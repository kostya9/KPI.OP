using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Threading.Tasks;
using System.Net.Sockets;

namespace Lab1.TcpClient
{
    public class Program
    {
        public static void Main(string[] args)
        {
            var endPoint = GetIpEndpoint();

            if (endPoint == null)
            {
                Console.WriteLine("Incorrect format. Exitting...");
                return;
            }

            var client = new LabTcpClient();
            Console.WriteLine("Type 'exit' to quit");
            client.StartSending(endPoint);

            Console.WriteLine("Press anything to exit...");
            Console.ReadKey();
            /*while (true)
            {
                string input = Console.ReadLine();

                if (input == "exit")
                    break;

                client.StartSending(input);
            }*/
        }

        private static IPEndPoint GetIpEndpoint()
        {
            Console.WriteLine("Type in the address of the server(with port)");
            string ipAndPort = Console.ReadLine();
            var ipAndPortArray = ipAndPort.Split(':');

            if (ipAndPortArray.Length != 2)
                return null;

            IPAddress address = null;
            var result = IPAddress.TryParse(ipAndPortArray[0], out address);
            if (!result)
                return null;

            int port = 0;
            result = int.TryParse(ipAndPortArray[1], out port);
            if (!result)
                return null;



            return new IPEndPoint(address, port);
        }
    }
}
