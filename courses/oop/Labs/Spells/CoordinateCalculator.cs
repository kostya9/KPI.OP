using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Spells.Domain;

namespace Spells
{
    // REFACTORING : replace methods with methods object
    class CoordinateCalculator
    {
        private readonly int _xMax;
        private readonly int _yMax;

        public CoordinateCalculator(int xMax,
            int yMax)
        {
            _xMax = xMax;
            _yMax = yMax;
        }

        public Vector2D ToCoordinate(Vector2D index)
        {
            return new Vector2D
            (
                index.X - _xMax / 2,
                index.Y - _yMax / 2
            );
        }

        public Vector2D ToArrayIndex(Vector2D coordinate)
        {
            return new Vector2D
            (
                coordinate.X + _xMax / 2,
                coordinate.Y + _yMax / 2
            );
        }
    }
}
