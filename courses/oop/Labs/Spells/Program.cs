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
            ConsoleField field = new ConsoleField();
            field.DrawBorder();
            field.Draw();

            while (!Console.KeyAvailable)
            {
                if (!field.UpdateMissles()) continue;
                field.Draw();
            }
            ConsoleKeyInfo key = Console.ReadKey();
            if(key.KeyChar == 'r')
                Main(new string[2]);
        }
    }
}
