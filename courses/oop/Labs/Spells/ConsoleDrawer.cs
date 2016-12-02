using System;
using Spells.Domain;

namespace Spells
{
    internal class ConsoleDrawer
    {
        static ConsoleDrawer()
        {
        }

        internal static void DrawMissle(Vector2D position)
        {
            ConsoleDrawer.WriteAtPosition('*', position);
        }

        internal static void DrawHealthyObject(Vector2D position, IHealthyObject obj)
        {
            if (obj == null)
            {
                ConsoleDrawer.ClearConsoleAt(position);
                return;
            }
            if(obj.HitPoints > obj.MaxHitPoints/2)
                ConsoleDrawer.WriteAtPosition('=', position);
            else if(obj.HitPoints > 0)
                ConsoleDrawer.WriteAtPosition('-', position);
            else
            {
                ConsoleDrawer.ClearConsoleAt(position);
            }
        }

        internal static void DrawMissleTail(Vector2D position)
        {
            ConsoleDrawer.WriteAtPosition('`', position);
        }

        internal static void DrawBorderSymbolAt(Vector2D position)
        {
            WriteAtPosition('%', position);
        }

        internal static void DrawSpell(Vector2D spellPosition)
        {
            WriteAtPosition('*', spellPosition);
        }

        internal static void DrawDirectionView(Vector2D directionViewPosition)
        {
            WriteAtPosition('\"', directionViewPosition);
        }

        internal static void ClearConsoleAt(Vector2D directionViewPosition)
        {
            WriteAtPosition(' ', directionViewPosition);
        }

        internal static void WriteAtPosition(char symbol, Vector2D curPosition)
        {
            Console.SetCursorPosition(curPosition.X, curPosition.Y);
            Console.Write(symbol);
        }
    }
}