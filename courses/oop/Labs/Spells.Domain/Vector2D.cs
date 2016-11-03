using System;
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

        public static Vector2D Round(double x,
            double y )
        {
            return new Vector2D((int)Math.Round(x), (int)Math.Round(y));
        }

        public Vector2D RotateBy45DegreesClockwise()
        {
            var sqrtTwo = Math.Sqrt(2);
            // Rotation matrix by pi/4
            var newX = X / sqrtTwo + Y / sqrtTwo;
            var newY = Y / sqrtTwo - X / sqrtTwo;
            return Round(newX, newY);
        }

        public Vector2D RotateBy45DegreesCounterClockwise()
        {
            var sqrtTwo = Math.Sqrt(2);
            // Rotation matrix by -pi/4
            var newX = X / sqrtTwo - Y / sqrtTwo;
            var newY = Y / sqrtTwo + X / sqrtTwo;
            return Round(newX, newY);
        }

        public override string ToString()
        {
            return $"X : {X}, Y : {Y}";
        }
    }
}