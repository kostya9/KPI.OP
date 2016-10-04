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
            field.CheckCollisionAndDraw();

            while (!Console.KeyAvailable)
            {
                if (!field.UpdateMissles()) continue;
                field.ClearMissles();
                field.CheckCollisionAndDraw();
            }
            Console.ReadLine();
        }
    }
}
