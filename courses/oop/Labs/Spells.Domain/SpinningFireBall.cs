using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Spells.Domain
{
    public class SpinningFireBall : FireBall
    {
        public SpinningFireBall() : base(Spells.SpinningFireBall)
        {
            
        }
        public override Missle Cast(Vector2D position,
            Vector2D direction)
        {
            var missle = base.Cast(position, direction);
            return new SpinningMissle(missle);
        }
    }
}
