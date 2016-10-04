using System;
using System.Collections.Generic;
using System.Configuration.Assemblies;
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
        private int[,] _field;
        private Dictionary<ICastable, Vector2D> _spells;
        private List<IDamagable> _objects;
        private List<Missle> _missles;
        private TimeSpan _lastUpdate;
        private Vector2D _fieldUpperLeft = new Vector2D (1, 1);

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
            _spells = new Dictionary<ICastable, Vector2D>
            {
                {new FireBall(_output), new Vector2D (-4, -4)},
                {new FireBall(_output), new Vector2D (4, 4)},
                {new FireBall(_output), new Vector2D (4, -4)},
            };
            _objects = new List<IDamagable>
            {
                //new Enemy(new Vector2D (0, 0), 1, 3)
            };
            _missles = new List<Missle>();
            _lastUpdate = TimeHelper.GetCurrentTime();
            var r = new Random();


            foreach (var spell in _spells)
            {
                var direction = new Vector2D (1 - r.Next(3), 1 - r.Next(3));
                _missles.Add(spell.Key.Cast(spell.Value, direction));
            }

            Spell testSpell = new SpinningFireBall(_output);
            _missles.Add(testSpell.Cast(new Vector2D(0, 0), new Vector2D(1, 0)));
        }

        public bool UpdateMissles()
        {
            if (GetDeltaTime() < TimeSpan.FromMilliseconds(FixedFrameDeltaMilliseconds))
                return false;

            _lastUpdate = TimeHelper.GetCurrentTime();

            foreach (var missle in _missles.ToList())
            {
                missle.UpdatePosition();

                if (!IsInTheField(missle.Position))
                    _missles.Remove(missle);
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

        private void UpdateObjects()
        {
            foreach (var obj in _objects.ToList())
                if (obj.Health == 0)
                    _objects.Remove(obj);
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

        public void AddMissle(Missle missle)
        {
            _missles.Add(missle);
        }

        public void CheckCollisionAndDraw()
        {
            Array.Clear(_field, 0, _field.Length);
            // TODO: volume calculation and drawing
            // TODO: object ASCII extended + health %
            foreach (var missle in _missles)
            {
                var index = ToIndex(missle.Position);
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
