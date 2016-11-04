using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Spells.Domain
{
    class PositionIsOccupiedException : ArgumentException
    {
        public PositionIsOccupiedException(Vector2D position) : base($"The position {position} is occupied")
        {
        }
    }
}
