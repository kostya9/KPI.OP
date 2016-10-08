using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices.ComTypes;
using System.Threading.Tasks;

namespace Lab1.TcpClient
{
    public class LabTcpClient
    {
        //private System.Net.Sockets.TcpClient _client;
        private readonly string HelpInfo;
        private readonly int Port = 5000;
        private readonly IPAddress Address = IPAddress.Parse("127.0.0.1");

        public LabTcpClient()
        {
            HelpInfo = File.ReadAllText("SupportedCommands.txt");
            //_client = new System.Net.Sockets.TcpClient();
        }

        public void StartSending(IPAddress address)
        {
            StartSending(address, Port).Wait();
        }

        public async Task StartSending(IPAddress address,
            int port )
        {
            

            using (var client = new System.Net.Sockets.TcpClient())
            {
                string message = "";
                try
                {
                    await client.ConnectAsync(address, port);
                }
                catch (Exception e)
                {
                    Console.WriteLine("Could not connet to the server. Exitting...");
                    return;
                }
                Console.WriteLine("Starting. Type in commands...");
                do
                {
                    try
                    {
                        message = Console.ReadLine();
                        if (message.ToLower() == "help")
                        {
                            Console.WriteLine(HelpInfo);
                            continue;
                        }
    
                        var writer = new StreamWriter(client.GetStream());
                        writer.WriteLine(message);
                        writer.Flush();
                        if (message.ToLower() == "stop")
                        {
                            return;
                        }
                        var reader = new StreamReader(client.GetStream());
                        Console.WriteLine(await reader.ReadLineAsync());
                    }
                    catch (Exception e)
                    {
                        Console.WriteLine($"Something bad hapenned : \n{e.Message}");
                        break;
                    }

                } while (client.Connected);

            }
        }
    }
}
