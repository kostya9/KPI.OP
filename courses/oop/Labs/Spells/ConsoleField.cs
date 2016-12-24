using System;
using System.Diagnostics;
using Spells.Domain;

namespace Spells
{
    internal class ConsoleField : IDisposable
    {
        private static readonly int FixedFrameDeltaMilliseconds;

        private readonly int[,] _field;
        private TimeSpan _lastUpdate;
        private readonly Vector2D _fieldUpperLeft = new Vector2D(1, 1);
        private SpellsGame Game => _gameReference.Target as SpellsGame;
        private readonly WeakReference _gameReference;
        private readonly CoordinateCalculator _calculator;
        private bool disposed;
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

            _gameReference = new WeakReference(new SpellsGame(IsInTheField));
            Game.MissleMoved += ((m,
                    e) =>
                {
                    var index = _calculator.ToArrayIndex(m.Position);
                    if (_field[index.X, index.Y] != (int)FieldCode.WallCode)
                        SetCodeAt(index, FieldCode.MissleCode);
                });
            Game.SpellCooldownZero += (SpellCooldownZeroHandler);
            Game.SpellsContainer.AddSpell(new FireBall(), new Vector2D(-4, -4));
            Game.SpellsContainer.AddSpell(new HealingBall(), new Vector2D(4, 4));
            Game.SpellsContainer.AddSpell(new SpinningFireBall(), new Vector2D(-4, 4));
            Game.SpellsContainer.AddSpell(new FireBall(), new Vector2D(4, -4));
            AddWall(new Vector2D(0, 0));
            AddWall(new Vector2D(0, 0));
            //_container.CastAllSpellsToRandomDirection();
            _lastUpdate = TimeHelper.GetCurrentTime();
        }

        public ConsoleField(string pathToSettings)
        {
            Console.SetWindowPosition(0, 0);
            Console.SetWindowSize(80, 40);
            _field = new int[31, 31];
            _calculator = new CoordinateCalculator(XMax, YMax);
            //Game = new SpellsGame(IsInTheField, pathToSettings);
            _lastUpdate = TimeHelper.GetCurrentTime();
        }

        private void AddWall(Vector2D position)
        {
            SetCodeAt(_calculator.ToArrayIndex(position), FieldCode.WallCode);
            Game.WallStore.CreateWall(position);
        }

        public bool Start()
        {
            DrawBorder();
            Draw();
            TimeHelper.Start();
            int odds = 20;
            Random r = new Random();
            //Main loop
            while (true)
            {
                // If were any updates - draw them
                if (Update())
                {
                    Draw();
                    // USE RELEASE MODE!!!
                    if (r.Next(odds) % (odds / 2) == 0)
                        GC.Collect();
                    if (Game == null)
                    {
                        Console.Clear();
                        Console.WriteLine("Game was cleared by GC");
                        Console.ReadKey();
                        return false;
                    }
                }

                if(!Console.KeyAvailable)
                    continue;

                ConsoleKeyInfo key = Console.ReadKey();
                if (key.Key == ConsoleKey.R)
                    return true;
                if (key.Key == ConsoleKey.Escape)
                    return false;
                if(key.Key == ConsoleKey.S)
                    Game.WallStore.SerializeFirst();
                if(key.Key == ConsoleKey.D)
                    Game.WallStore.DeserializeFirst();
            }

            // r for restart

        }


        private bool Update()
        {
            // Fixed framerate
            if (GetDeltaTime() < TimeSpan.FromMilliseconds(FixedFrameDeltaMilliseconds))
                return false;
            Game.Update();
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
                    var healthyObject = Game.WallStore.GetHealthyObjectAt(coordinate);
                    //Delete object if it's gone
                    if(healthyObject == null || healthyObject.HitPoints == 0) 
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
            Game.SpellsContainer.CastSpell(spell, newMissleDirection);
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

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected void Dispose(bool disposing)
        {
            if (this.disposed)
                return;
            if (disposing)
            {
                Game.Dispose();
            }

            this.disposed = true;
        }

        ~ConsoleField()
        {
            this.Dispose(false);
        }
    }
}
