using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Spells.Domain
{
    public class HealingBall : Spell
    {
        protected HealingBall(Spells id) : base((int)id, id.ToString(), 1, 1, 1, TimeSpan.FromSeconds(10), "HHHHEAL")
        {

        }

        public HealingBall() : this(Spells.HealingBall)
        {
            
        }

        public override Missle Cast(Vector2D position,
    Vector2D direction)
        {
            // REFACTORING : insert reasining variable
            var healingRate = 1;
            var missle = base.Cast(position, direction);
            return new HealingMissle(missle, healingRate);
        }
    }
}
