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

        private readonly int[,] _field;
        private TimeSpan _lastUpdate;
        private readonly Vector2D _fieldUpperLeft = new Vector2D(1, 1);
        private readonly SpellsContainer _container;
        private readonly CoordinateCalculator _calculator;

        private int XMax => _field.GetUpperBound(0) + 1;

        private int YMax => _field.GetUpperBound(1) + 1;

        static ConsoleField()
        {
            FixedFrameDeltaMilliseconds = 700;
        }

        public ConsoleField()
        {
            Console.SetWindowPosition(0, 0);
            Console.SetWindowSize(80, 40);
            _field = new int[31, 31];
            _calculator = new CoordinateCalculator(XMax, YMax);

            _container = new SpellsContainer(this.IsInTheField);
            _container.SubscribeToMissleMove(MissleMovedHandler);
            _container.SubscribeToCooldownZero(this.SpellCooldownZeroHandler);
            _container.AddSpell(new FireBall(), new Vector2D(-4, -4));
            _container.AddSpell(new FireBall(), new Vector2D(4, 4));
            _container.AddSpell(new FireBall(), new Vector2D(4, -4));
            _container.AddSpell(new SpinningFireBall(), new Vector2D(-4, 4));
            //_container.CastAllSpellsToRandomDirection();
            _lastUpdate = TimeHelper.GetCurrentTime();
        }


        public bool UpdateMissles()
        {
            if (GetDeltaTime() < TimeSpan.FromMilliseconds(FixedFrameDeltaMilliseconds))
                return false;
            _container.Update();
            _lastUpdate = TimeHelper.GetCurrentTime();
            return true;
        }

        private bool IsInTheField(Vector2D position)
        {
            var xMax = XMax;
            var yMax = YMax;
            var indexPos = _calculator.ToArrayIndex(position);
            return (indexPos.X < xMax) &&
                   (indexPos.Y < yMax) &&
                   (indexPos.X >= 0) &&
                   (indexPos.Y >= 0);
        }

        private TimeSpan GetDeltaTime()
        {
            return TimeHelper.GetCurrentTime() - _lastUpdate;
        }

        private void MissleMovedHandler(Missle missle,
            MissleMovedHandlerArgs args)
        {
            var index = _calculator.ToArrayIndex(missle.Position);
            if (_field[index.X, index.Y] == (int) FieldCode.MissleCode)
                Debug.Write("Boom!\n");
            _field[index.X, index.Y] = (int) FieldCode.MissleCode;
        }

        public void Start()
        {
            this._container.StartMeasuringTime();
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

        public void Draw()
        {
            for (var x = 0; x < XMax; x++)
            {
                for (var y = 0; y < YMax; y++)
                {
                    DrawAtPositionAndChangeCode(x, y);
                }
            }
        }

        private void DrawAtPositionAndChangeCode(int x,
            int y)
        {
            switch ((FieldCode) _field[x, y])
            {
                case FieldCode.TrailCode:
                {
                    Console.SetCursorPosition(_fieldUpperLeft.X + x, _fieldUpperLeft.Y + y);
                    Console.Write("`");
                    _field[x, y] = (int) FieldCode.Nothing;
                }
                    break;
                case FieldCode.MissleCode:
                {
                    Console.SetCursorPosition(_fieldUpperLeft.X + x, _fieldUpperLeft.Y + y);
                    Console.Write("*");
                    _field[x, y] = (int) FieldCode.TrailCode;
                }
                    break;
                case FieldCode.Nothing:
                {
                    Console.SetCursorPosition(_fieldUpperLeft.X + x, _fieldUpperLeft.Y + y);
                    Console.Write(" ");
                }
                    break;
            }
        }

        private void SpellCooldownZeroHandler(ICastable spell,
            SpellCooldownZeroEventArgs args)
        {
            _container.StopMeasuringTime();

            var pos = _calculator.ToArrayIndex(args.Position);
            Console.SetCursorPosition(pos.X, pos.Y);
            var prevColor = Console.ForegroundColor;
            Console.ForegroundColor = ConsoleColor.Red;
            Console.Write("*");

            var enteredKey = ConsoleKey.X;
            var currentDirection = new Vector2D(1, 1);

            while (enteredKey != ConsoleKey.Enter)
            {
                var curPosition = pos + currentDirection;
                enteredKey = Console.ReadKey().Key;
                if (enteredKey == ConsoleKey.LeftArrow)
                {
                    Console.SetCursorPosition(curPosition.X, curPosition.Y);
                    Console.Write(" ");
                    currentDirection = getNextDirectionClockwise(currentDirection);
                }
                else if (enteredKey == ConsoleKey.RightArrow)
                {
                    Console.SetCursorPosition(curPosition.X, curPosition.Y);
                    Console.Write(" ");
                    currentDirection = getNextDirectionCounterClockwise(currentDirection);
                }

                curPosition = pos + currentDirection;
                Console.SetCursorPosition(curPosition.X, curPosition.Y);
                Console.Write("\"");
            }

            Console.ForegroundColor = prevColor;
            _container.CastSpell(spell, currentDirection);
            _container.StartMeasuringTime();
    }

        private Vector2D getNextDirectionClockwise(Vector2D prevDirection)
        {
            if (prevDirection.X == 1)
            {
                if (prevDirection.Y == 1)
                {
                    return new Vector2D(1, -1);
                }
                return new Vector2D(-1, -1);
            }
            if (prevDirection.Y == 1)
            {
                return new Vector2D(1, 1);
            }
            return new Vector2D(-1, 1);
        }

        private Vector2D getNextDirectionCounterClockwise(Vector2D prevDirection)
        {
            if (prevDirection.X == 1)
            {
                if (prevDirection.Y == 1)
                {
                    return new Vector2D(-1, 1);
                }
                return new Vector2D(1, 1);
            }
            if (prevDirection.Y == 1)
            {
                return new Vector2D(-1, -1);
            }
            return new Vector2D(1, -1);
        }
    }
}
