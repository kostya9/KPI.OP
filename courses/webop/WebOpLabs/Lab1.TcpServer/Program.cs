using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using Domain;
using Newtonsoft.Json;

namespace Lab1.TcpServer
{
    public class Program
    {
        public static void Main(string[] args)
        {
            var bags = Bag.GetInitializedBags();
            int port = GetPort();
            if (port < 0)
            {
                Console.WriteLine("Incorrect format. Exitting...");
                return;
            }

            LabTcpServer server = new LabTcpServer(bags, port);
            server.Start();
            //Console.ReadLine();
        }

        private static int GetPort()
        {
            Console.WriteLine("Enter the port :");
            var input = Console.ReadLine();
            int inputNumber = 0;
            var result = int.TryParse(input, out inputNumber);

            if (!result)
                return -1;

            return inputNumber;
        }
    }
}
