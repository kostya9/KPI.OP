using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Spells.ConsoleOutput
{
    class Program
    {
        static void Main(string[] args)
        {
            while (true)
            {
                using (ConsoleField field = new ConsoleField())
                {
                    if (field.Start() == false)
                        break;
                }
            }
        }
    }
}
