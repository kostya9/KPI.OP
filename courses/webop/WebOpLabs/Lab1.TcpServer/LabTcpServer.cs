using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Http.Headers;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Domain;
using Newtonsoft.Json;
using Mono.Options;

namespace Lab1.TcpServer
{
    public class LabTcpServer
    {
        private IEnumerable<Bag> _bags;
        private TcpListener _listener;
        private static readonly int Port = 5000;
        private static readonly IPAddress Address = IPAddress.Any;
        private static readonly double MinutesAlive = 2;
        private List<TcpClient> _clients;

        public LabTcpServer(IEnumerable<Bag> bags)
        {
            _listener = new TcpListener(Address, Port);
            _bags = bags;
            _clients = new List<TcpClient>();
        }

        public void Start()
        {
            Console.WriteLine($"Started a server on {Address}:{Port}");
            _listener.Start();
            while (true)
            {
                //var result = await _listener.AcceptTcpClientAsync();
                // TODO: Async or notAsync - the question
                var client = _listener.AcceptTcpClientAsync().GetAwaiter().GetResult();
                lock (_clients)
                {
                    _clients.Add(client);
                }
                ThreadPool.QueueUserWorkItem(Accept, client);
            }
        }

        private void Accept(object client)
        {
            Accept((TcpClient) client);
        }

        private void Accept(TcpClient client)
        {
            var clientDisplayName = client.Client.RemoteEndPoint.ToString();
            try
            {
                using (var stream = client.GetStream())
                {
                    LogInfo(clientDisplayName, "Connected");
                    var reader = new StreamReader(stream);
                    var writer = new StreamWriter(stream);
                    do
                    {
                        LogInfo(clientDisplayName, "Waiting for commands...");

                        string data;
                        if (!GetCommand(reader, clientDisplayName, out data))
                            break;
                        LogInfo(clientDisplayName, $"Message received:{data}");

                        if (IsCommandToStop(data))
                        {
                            LogInfo(clientDisplayName, "Disconnecting due to user command...");
                            break;
                        }

                        if (!client.Connected)
                        {
                            LogInfo(clientDisplayName, "Client disconnected on it's own...");
                            break;
                        }

                        SendResponse(data, clientDisplayName, writer);
                    } while (true);
                }
            }
            catch (Exception e)
            {
                LogInfo("Error", e.Message);
            }
            finally
            {
                LogInfo(clientDisplayName, "Disconnected");
                lock (_clients)
                {
                    _clients.Remove(client);
                }
            }
        }

        private bool GetCommand(StreamReader reader,
            string clientDisplayName,
            out string data)
        {
            var t = reader.ReadLineAsync();
            if (!t.Wait((int) TimeSpan.FromMinutes(MinutesAlive).TotalMilliseconds))
            {
                LogInfo(clientDisplayName, $"No commands for {MinutesAlive} minutes. Disconnecting...");
                data = "";
                return false;
            }

            data = t.GetAwaiter().GetResult();
            return true;
        }

        private void SendResponse(string receivedMessage,
            string clientDisplayName,
            StreamWriter writer)
        {
            var response = GetResponse(receivedMessage) ??
                           "Command syntax incorrect. Try checking help.";

            writer.WriteLine(response);
            writer.Flush();
            LogInfo(clientDisplayName, "Sent answer");
        }

        private string GetResponse(string command)
        {
            string mainCommand;
            var position = CheckMainCommand(command, out mainCommand);

            switch (mainCommand.ToLower())
            {
                case "get clients":
                {
                    var response = new StringBuilder();
                    lock (_clients)
                    {
                        foreach (var client in _clients)
                            response.Append(client.Client.RemoteEndPoint + " ");
                    }
                    return $"Clients : {response}";
                }
                case "get count":
                {
                    return $"Objects count : {_bags.Count()}";
                }
                case "get data":
                {
                    if (position < 0)
                        return JsonConvert.SerializeObject(_bags, Formatting.None,
                            new JsonSerializerSettings {NullValueHandling = NullValueHandling.Ignore});
                        var optionsDictionary = ParseOptions(command, position);

                        /*if (optionsDictionary == null)
                            return null;*/

                        var copyBags = _bags.ToList();

                        if (optionsDictionary.ContainsKey("p"))
                        {
                            var fieldName = optionsDictionary["p"];

                            if (!Bag.FieldExists(fieldName))
                                return $"There is no property {fieldName} in the JSON";

                            copyBags = FilterBags(optionsDictionary, copyBags, fieldName);

                            if (copyBags == null)
                                return "Incorrect format. Try checking help.";
                        }

/*                        if (optionsDictionary.Count > 0)
                            return null;*/

                        return JsonConvert.SerializeObject(copyBags, Formatting.None,
                            new JsonSerializerSettings { NullValueHandling = NullValueHandling.Ignore });
                 }
                default:
                {
                    return null;
                }
            }
        }

        private List<Bag> FilterBags(Dictionary<string, string> optionsDictionary,
            List<Bag> copyBags,
            string fieldName)
        {
            if (optionsDictionary.ContainsKey("g"))
            {
                var value = optionsDictionary["g"];
                try
                {
                    copyBags = GetFilteredMoreThan(copyBags, value, fieldName).ToList();
                }
                catch (FormatException e)
                {
                    LogInfo("Error", "Incorrect format for command");
                    copyBags = null;
                }
            }

            if (optionsDictionary.ContainsKey("l"))
            {
                var value = optionsDictionary["l"];
                try
                {
                    copyBags = GetFilteredLessThan(copyBags, value, fieldName).ToList();
                }
                catch (FormatException e)
                {
                    LogInfo("Error", "Incorrect format for command");
                    copyBags = null;
                }
            }

            if (optionsDictionary.ContainsKey("s"))
            {
                if (optionsDictionary["s"] == "asc")
                    copyBags = copyBags.OrderBy(x => x[fieldName]).ToList();
                else if (optionsDictionary["s"] == "desc")
                    copyBags = copyBags.OrderBy(x => x[fieldName]).ToList();
                else
                    copyBags = null;
            }
            return copyBags;
        }

        private int CompareTo(Bag bag,
            string value,
            string fieldName)
        {
            var field = bag[fieldName];
            var result = 0;

            var dateTimeFormat = "yyyy_MM_dd_HH:mm";

            var switcher = new Dictionary<Type, Action>()
            {
                {typeof(string), () => result = string.CompareOrdinal((string) field, value)},
                {typeof(int), () => result = ((int) field).CompareTo(int.Parse(value))},
                {
                    typeof(DateTime),
                    () => result = ((DateTime) field).CompareTo(DateTime.ParseExact(value, dateTimeFormat, null))
                }
            };

            switcher[field.GetType()]();

            return result;
        }

        private IEnumerable<Bag> GetFilteredLessThan(IEnumerable<Bag> bags,
            string value,
            string fieldName)
        {
            return bags.Where(b => CompareTo(b, value, fieldName) < 0);
        }

        private IEnumerable<Bag> GetFilteredMoreThan(IEnumerable<Bag> bags,
            string value,
            string fieldName)
        {
            return bags.Where(b => CompareTo(b, value, fieldName) > 0);
        }

        private int CheckMainCommand(string command,
            out string mainCommand)
        {
            var tempCommand = command;

            var position = command.IndexOf('-');

            if (position >= 0)
                tempCommand = command.Substring(0, position);

            tempCommand = tempCommand.Trim();
            mainCommand = tempCommand;

            return position;
        }

        private Dictionary<string, string> ParseOptions(string command,
            int position)
        {
            var options = command.Substring(position).Split('-');
            var optionsDictionary = new Dictionary<string, string>();
            foreach (var option in options)
            {
                if (option == "")
                    continue;

                var optionWords = option.Split(' ');

                if (optionWords.Length < 2)
                {
                    optionsDictionary[optionWords[0]] = "";
                    continue;
                }

                optionsDictionary[optionWords[0]] = optionWords[1];
            }
            return optionsDictionary;
        }

        private void LogInfo(string name,
            string info)
        {
            Console.WriteLine($"[{name}] {info} ");
        }

        private bool IsCommandToStop(string command)
        {
            return command == "Stop\n";
        }

        private bool IsTimeExceeded(DateTime timeStarted)
        {
            return timeStarted.AddMinutes(MinutesAlive) < DateTime.Now;
        }
    }
}

