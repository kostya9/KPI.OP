using System;
using System.Collections.Generic;
using System.Configuration.Assemblies;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Spells.Domain;

namespace Spells
{
    internal class ConsoleField
    {
        private static readonly int FixedFrameDeltaMilliseconds;

        private readonly Stream _output = Console.OpenStandardOutput();
        private readonly int[,] _field;
        private TimeSpan _lastUpdate;
        private Vector2D _fieldUpperLeft = new Vector2D (1, 1);
        private readonly SpellsContainer _container = new SpellsContainer();

        private int XMax => _field.GetUpperBound(0) + 1;

        private int YMax => _field.GetUpperBound(1) + 1;

        static ConsoleField()
        {
            FixedFrameDeltaMilliseconds = 700;
            Console.SetWindowPosition(0, 0);
            Console.SetWindowSize(100, 60);
        }

        public ConsoleField()
        {
            _field = new int[41, 41]; // Not even !
            _container.AddSpell(new FireBall(_output), new Vector2D (-4, -4));
            _container.AddSpell(new FireBall(_output), new Vector2D(4, 4));
            _container.AddSpell(new FireBall(_output), new Vector2D(4, -4));
            _container.AddSpell(new SpinningFireBall(_output), new Vector2D(-4, 4));
            _container.CastAllSpellsToRandomDirection();
            _lastUpdate = TimeHelper.GetCurrentTime();
        }


        public bool UpdateMissles()
        {
            if (GetDeltaTime() < TimeSpan.FromMilliseconds(FixedFrameDeltaMilliseconds))
                return false;

            _lastUpdate = TimeHelper.GetCurrentTime();

            foreach (var missle in _container.Missles.ToList())
            {
                missle.UpdatePosition();

                if (!IsInTheField(missle.Position))
                    _container.RemoveMissle(missle);
            }
            return true;
        }

        private bool IsInTheField(Vector2D position)
        {
            var xMax = XMax;
            var yMax = YMax;
            var indexPos = ToIndex(position);
            return (indexPos.X < xMax) &&
                   (indexPos.Y < yMax) &&
                   (indexPos.X >= 0) &&
                   (indexPos.Y >= 0);
        }

        private TimeSpan GetDeltaTime()
        {
            return TimeHelper.GetCurrentTime() - _lastUpdate;
        }

        public void ClearMissles()
        {
            for (var x = 0; x < XMax; x++)
            {
                for (var y = 0; y < YMax; y++)
                {
                    Console.SetCursorPosition(_fieldUpperLeft.X + x, _fieldUpperLeft.Y + y);
                    if (_field[x, y] == 1)
                    {
                        Console.Write("`");
                    }
                    else
                    {
                        Console.Write(" ");   
                    }
                }
            }
        }

        private Vector2D ToCoordinate(Vector2D index)
        {
            return new Vector2D
            (
                index.X - XMax/2,
                index.Y - YMax/2
            );
        }

        private Vector2D ToIndex(Vector2D coordinate)
        {
            return new Vector2D
            (
                coordinate.X + XMax/2,
                coordinate.Y + YMax/2
            );
        }

        public void DrawBorder()
        {
            var xMax = XMax;
            var yMax = YMax;

            for (var i = 0; i < xMax; i++)
            {
                Console.SetCursorPosition(_fieldUpperLeft.X + i, _fieldUpperLeft.Y - 1);
                Console.Write("%");
                Console.SetCursorPosition(_fieldUpperLeft.X + i, _fieldUpperLeft.Y + yMax);
                Console.Write("%");
            }

            for (var i = 0; i < yMax; i++)
            {
                Console.SetCursorPosition(_fieldUpperLeft.X - 1, _fieldUpperLeft.Y + i);
                Console.Write("%");
                Console.SetCursorPosition(_fieldUpperLeft.X + xMax, _fieldUpperLeft.Y + i);
                Console.Write("%");
            }
        }

        public void CheckCollisionAndDraw()
        {
            Array.Clear(_field, 0, _field.Length);
            // TODO: volume calculation and drawing
            // TODO: object ASCII extended + health %
            foreach (var missle in _container.Missles)
            {
                var index = ToIndex(missle.Position);
                if(_field[index.X, index.Y] == 1)
                    Debug.Write("Boom!\n");
                _field[index.X, index.Y] = 1;
            }

            for (var x = 0; x < XMax; x++)
            {
                for (var y = 0; y < YMax; y++)
                {
                    Console.SetCursorPosition(_fieldUpperLeft.X + x, _fieldUpperLeft.Y + y);
                    Console.Write(_field[x, y] == 1 ? "*" : "");
                }
            }
        }
    }
}
