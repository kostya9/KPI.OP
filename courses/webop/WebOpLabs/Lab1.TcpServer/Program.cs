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
            const string pathToBags = "bags.json";
            if (!File.Exists(pathToBags))
            {
                File.WriteAllText(pathToBags, JsonConvert.SerializeObject(bags));
            }
            else
            {
                bags = JsonConvert.DeserializeObject<List<Bag>>(File.ReadAllText(pathToBags));
            }
            LabTcpServer server = new LabTcpServer(bags);
            server.Start();
            Console.ReadLine();
        }
    }
}
