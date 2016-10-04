using System.CodeDom;

namespace Spells.Domain
{
    public struct Vector2D
    {
        public readonly int X;
        public readonly int Y;

        public Vector2D(int x,
            int y)
        {
            X = x;
            Y = y;
        }

        public static Vector2D operator +(Vector2D first,
            Vector2D second)
        {
            return new Vector2D(
                first.X + second.X,
                first.Y + second.Y
            );
        }

        public static Vector2D operator -(Vector2D first,
            Vector2D second)
        {
            return new Vector2D(
                first.X - second.X,
                first.Y - second.Y
            );
        }

        public override string ToString()
        {
            return $"X : {X}, Y : {Y}";
        }
    }
}