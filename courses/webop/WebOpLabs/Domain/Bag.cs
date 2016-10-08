using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Domain
{
    public class Bag
    {

        public object this[string name] => this.GetType().GetRuntimeProperty(name).GetValue(this, null);

        public int Id { get; set; }
        public string Name { get; set; }
        public DateTime TimeCreation { get; set; }
        public DateTime? TimeBought { get; set; }
        public string Owner { get; set; }
        public string Factory { get; set; }
        public string Description { get;set; }
        public string ImageLink{ get;set; }

        public static bool FieldExists(string name)
        {
            var prop = typeof(Bag).GetRuntimeProperty(name);
            return prop != null;
        }

        public static List<Bag> GetInitializedBags()
        {
            List<Bag> bags = new List<Bag>()
            {
                new Bag() { Name = "BagSuper", Factory = "Zimbab", Owner = "Slaughter", Id=123, TimeBought = null, TimeCreation = DateTime.Now},
                new Bag() { Name = "Crator", Factory = "Viba", Owner = "Gus'", Id=321, TimeBought = DateTime.Now.AddDays(-1), TimeCreation = DateTime.Now.AddDays(-2)},
                new Bag() { Name = "Bacor", Factory = "Westwend", Owner = "Asgall Druiminn", Id=1234, TimeBought = DateTime.Now.AddDays(-3), TimeCreation = DateTime.Now.AddMonths(-12)},
                new Bag() { Name = "Latisha", Factory = "Haedleigh", Owner = "Pòl MacIllIanain", Id=1236, TimeBought = null, TimeCreation = DateTime.Now.AddMonths(-111)},
                new Bag() { Name = "Enriqueta", Factory = "Ballinamallard", Owner = "Dubh-shìth Cèampach", Id=1231, TimeBought = null, TimeCreation = DateTime.Now.AddMonths(-4)},
                new Bag() { Name = "Nona", Factory = "City of Fire", Owner = "Rgoan", Id=1239, TimeBought = DateTime.Now.AddDays(-25), TimeCreation = DateTime.Now.AddMonths(-6)},
                new Bag() { Name = "Hoyt", Factory = "Northwich", Owner = "Baradiel", Id=1238, TimeBought = DateTime.Now.AddDays(-15), TimeCreation = DateTime.Now.AddMonths(-9)},
                new Bag() { Name = "Meggan", Factory = "Hull", Owner = "Naooo", Id=12387, TimeBought = DateTime.Now.AddDays(-11), TimeCreation = DateTime.Now.AddMonths(-3)},
                new Bag() { Name = "Tabitha", Factory = "Whiteridge", Owner = "Bhuchung", Id=12342, TimeBought = null, TimeCreation = DateTime.Now.AddMonths(-12)},
                new Bag() { Name = "Vesta", Factory = "Elinmylly", Owner = "Wangdup", Id=12341, TimeBought = DateTime.Now.AddDays(-7), TimeCreation = DateTime.Now.AddMonths(-21)},
                new Bag() { Name = "Adolfo", Factory = "Sanlow", Owner = "Rigzin", Id=12387, TimeBought = DateTime.Now.AddDays(-4), TimeCreation = DateTime.Now.AddMonths(-31)},
                new Bag() { Name = "Twyla", Factory = "Kameeraska", Owner = "Kundang Nepali", Id=12312, TimeBought = DateTime.Now.AddDays(-9), TimeCreation = DateTime.Now.AddMonths(-4)}
            };

            return bags;
        }
    }
}
