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
            _container.CastAllSpellsToRandomDirection();
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
            if (_field[index.X, index.Y] == (int)FieldCode.MissleCode)
                Debug.Write("Boom!\n");
            _field[index.X, index.Y] = (int)FieldCode.MissleCode;
        }

        public void DrawBorder()
        {
            var xMax = XMax;
            var yMax = YMax;

            DrawHorizontalBorders(xMax, yMax);
            DrawVerticalBorders(xMax, yMax);
        }

        private void DrawVerticalBorders(int xMax, int yMax)
        {
            for (var i = 0; i < yMax; i++)
            {
                ConsoleDrawer.DrawBorderSymbolAt(new Vector2D(_fieldUpperLeft.X - 1, _fieldUpperLeft.Y + i));
                ConsoleDrawer.DrawBorderSymbolAt(new Vector2D(_fieldUpperLeft.X + xMax, _fieldUpperLeft.Y + i));
            }
        }

        private void DrawHorizontalBorders(int xMax, int yMax)
        {
            for (var i = 0; i < xMax; i++)
            {
                ConsoleDrawer.DrawBorderSymbolAt(new Vector2D(_fieldUpperLeft.X + i, _fieldUpperLeft.Y - 1));
                ConsoleDrawer.DrawBorderSymbolAt(new Vector2D(_fieldUpperLeft.X + i, _fieldUpperLeft.Y + yMax));
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
            var consolePosition = new Vector2D(_fieldUpperLeft.X + x, _fieldUpperLeft.Y + y);
            var arrayPosition = new Vector2D(x, y);
            switch ((FieldCode)_field[x, y])
            {
                case FieldCode.TrailCode:
                    {
                        ConsoleDrawer.DrawMissleTail(consolePosition);
                        SetCodeAt(arrayPosition, FieldCode.Nothing);
                    }
                    break;
                case FieldCode.MissleCode:
                    {
                        ConsoleDrawer.DrawMissle(consolePosition);
                        SetCodeAt(arrayPosition, FieldCode.TrailCode);
                    }
                    break;
                case FieldCode.Nothing:
                    {
                        ConsoleDrawer.ClearConsoleAt(consolePosition);
                    }
                    break;
            }
        }

        private void SpellCooldownZeroHandler(ICastable spell,
            SpellCooldownZeroEventArgs args)
        {
            var newMissleDirection = GetNewMissleDirection(args.Position);
            _container.CastSpell(spell, newMissleDirection);
        }

        private Vector2D GetNewMissleDirection(Vector2D spellPosition)
        {
            var prevColor = Console.ForegroundColor;
            var enteredKey = ConsoleKey.X;
            var currentDirection = new Vector2D(1, 1);
            Console.ForegroundColor = ConsoleColor.Red;

            while (enteredKey != ConsoleKey.Enter)
            {
                ConsoleDrawer.DrawSpell(spellPosition);
                var directionViewPosition = spellPosition + currentDirection;
                enteredKey = Console.ReadKey().Key;
                if (enteredKey == ConsoleKey.LeftArrow)
                {
                    ConsoleDrawer.ClearConsoleAt(directionViewPosition);
                    currentDirection = getNextDirectionClockwise(currentDirection);
                }
                else if (enteredKey == ConsoleKey.RightArrow)
                {
                    ConsoleDrawer.ClearConsoleAt(directionViewPosition);
                    currentDirection = getNextDirectionCounterClockwise(currentDirection);
                }
                directionViewPosition = spellPosition + currentDirection;
                ConsoleDrawer.DrawDirectionView(directionViewPosition);
            }

            Console.ForegroundColor = prevColor;
            return currentDirection;
        }

        private Vector2D getNextDirectionClockwise(Vector2D prevDirection)
        {
            return prevDirection.RotateBy45DegreesClockwise();
        }

        private Vector2D getNextDirectionCounterClockwise(Vector2D prevDirection)
        {
            return prevDirection.RotateBy45DegreesCounterClockwise();
        }

        private void SetCodeAt(Vector2D position,
            FieldCode code)
        {
            _field[position.X, position.Y] = (int)code;
        }
    }
}
