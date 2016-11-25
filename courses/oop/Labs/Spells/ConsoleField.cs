using System;
using System.Diagnostics;
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

            _container = new SpellsContainer(IsInTheField);
            _container.SubscribeToMissleMove(MissleMovedHandler);
            _container.SubscribeToCooldownZero(SpellCooldownZeroHandler);
            _container.AddSpell(new FireBall(), new Vector2D(-4, -4));
            _container.AddSpell(new FireBall(), new Vector2D(4, 4));
            _container.AddSpell(new SpinningFireBall(), new Vector2D(-4, 4));
            AddWall(new Vector2D(0, 0));
            //_container.CastAllSpellsToRandomDirection();
            _lastUpdate = TimeHelper.GetCurrentTime();
        }

        private void AddWall(Vector2D position)
        {
            SetCodeAt(_calculator.ToArrayIndex(position), FieldCode.WallCode);
            _container.AddWall(position);
        }

        public void Start()
        {
            DrawBorder();
            Draw();
            TimeHelper.Start();

            // Test cooldown exception
            var fireBall = new FireBall();
            _container.AddSpell(fireBall, new Vector2D(4, -4));
            try
            {
                _container.CastSpell(fireBall, new Vector2D(1, 1));
                _container.CastSpell(fireBall, new Vector2D(1, -1));
            }
            catch (CooldownException e)
            {
                Debug.Write($"The spell casted from {e.Args.Position} at direction {e.Args.Direction} is on cooldown. \nTry cast again in {e.Args.RemainingTime} ");
            }

            //Main loop
            while (!Console.KeyAvailable)
            {
                // If were any updates - draw them
                if (Update())
                    Draw();
            }

            // r for restart
            ConsoleKeyInfo key = Console.ReadKey();
            if (key.KeyChar == 'r')
                Start();
        }


        private bool Update()
        {
            // Fixed framerate
            if (GetDeltaTime() < TimeSpan.FromMilliseconds(FixedFrameDeltaMilliseconds))
                return false;
            _container.Update();
            _lastUpdate = TimeHelper.GetCurrentTime();
            return true;
        }

        // To have an ability to delete something if it's gone from the field
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
            if(_field[index.X, index.Y] != (int)FieldCode.WallCode)
                SetCodeAt(index, FieldCode.MissleCode);
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
                    DrawAtPositionAndChangeCode(new Vector2D(x, y));
                }
            }
        }

        private void DrawAtPositionAndChangeCode(Vector2D position)
        {
            var consolePosition = new Vector2D(_fieldUpperLeft.X + position.X, _fieldUpperLeft.Y + position.Y);
            switch ((FieldCode)_field[position.X, position.Y])
            {
                case FieldCode.TrailCode:
                    {
                        ConsoleDrawer.DrawMissleTail(consolePosition);
                        SetCodeAt(position, FieldCode.Nothing);
                    }
                    break;
                case FieldCode.MissleCode:
                    {
                        ConsoleDrawer.DrawMissle(consolePosition);
                        SetCodeAt(position, FieldCode.TrailCode);
                    }
                    break;
                case FieldCode.Nothing:
                    {
                        ConsoleDrawer.ClearConsoleAt(consolePosition);
                    }
                    break;
                case FieldCode.WallCode:
                {
                    var coordinate = _calculator.ToCoordinate(position);
                    var healthyObject = _container.GetHealthyObjectAt(coordinate);
                    //Delete object if it's gone
                    if(healthyObject.HitPoints == 0) 
                        SetCodeAt(position, FieldCode.Nothing);
                    ConsoleDrawer.DrawHealthyObject(consolePosition, healthyObject);
                }
                break;
            }
        }

        private void SpellCooldownZeroHandler(ICastable spell,
            SpellCooldownZeroEventArgs args)
        {
            Debug.WriteLine(TimeHelper.GetCurrentTime());
            TimeHelper.Stop();
            var newMissleDirection = GetNewMissleDirection(_calculator.ToArrayIndex(args.Position));
            _container.CastSpell(spell, newMissleDirection);
            TimeHelper.Start();
        }

        // Prompt the user to direct the missle
        private Vector2D GetNewMissleDirection(Vector2D spellPosition)
        {
            var prevColor = Console.ForegroundColor;
            var enteredKey = ConsoleKey.X;
            var currentDirection = new Vector2D(1, 1);
            var directionViewPosition = spellPosition + currentDirection;
            Console.ForegroundColor = ConsoleColor.Red;

            while (enteredKey != ConsoleKey.Enter)
            {
                ConsoleDrawer.DrawSpell(spellPosition);
                
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
            ConsoleDrawer.ClearConsoleAt(spellPosition);
            ConsoleDrawer.ClearConsoleAt(directionViewPosition);
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
