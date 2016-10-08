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
            Console.WriteLine("Type in the address of the server");
            string ip = Console.ReadLine();

            var client = new LabTcpClient();
            Console.WriteLine("Type 'exit' to quit");
            IPAddress address;
            try
            {
                address = IPAddress.Parse(ip);
            }
            catch (FormatException e)
            {
                Console.WriteLine("Incorrect format. Closing...");
                return;
            }

            client.StartSending(address);

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
    }
}
