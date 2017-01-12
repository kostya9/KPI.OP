using System.ComponentModel;
using Spells.Editor.ViewModel;

namespace Spells.Editor.Model
{
    public class Vector2D : BindableBase
    {
        private int _x;
        private int _y;

        public int X
        {
            get { return _x; }
            set { SetProperty(ref _x, value); }
        }

        public int Y
        {
            get { return _y; }
            set { SetProperty(ref _y, value); }
        }

        public Vector2D(int x,
            int y)
        {
            X = x;
            Y = y;
        }

        public override string ToString()
        {
            return $"X : {X}, Y : {Y}";
        }

        public bool Equals(Vector2D other)
        {
            return (X == other.X) && (Y == other.Y);
        }

        public override int GetHashCode()
        {
            unchecked
            {
                return (X * 397) ^ Y;
            }
        }

        public static bool operator ==(Vector2D first,
            Vector2D second)
        {
            if ((object)first == null && (object)second == null)
                return true;
            if ((object)first == null || (object)second == null)
                return false;
            return first.Equals(second);
        }

        public static bool operator !=(Vector2D first,
    Vector2D second)
        {
            return !(first == second);
        }
    }
}