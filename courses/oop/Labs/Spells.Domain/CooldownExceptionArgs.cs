using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Spells.Domain
{
    public class CooldownExceptionArgs
    {
        public CooldownExceptionArgs(Vector2D direction,
            Vector2D position,
            ICastable castable,
            TimeSpan remainingTime)
        {
            Direction = direction;
            Position = position;
            Castable = castable;
            RemainingTime = remainingTime;
        }

        public ICastable Castable { get; }
        public Vector2D Position { get; }
        public Vector2D Direction { get;  }
        public TimeSpan RemainingTime { get; }
    }
}
