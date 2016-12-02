using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;

namespace Spells.Domain
{
    class HealingMissle : Missle
    {
        public int Healing { get; }

        public HealingMissle(Spell castedSpell,
            Vector2D position,
            Vector2D direction,
            TimeSpan timeCasted, int healing) : base(castedSpell, position, direction, timeCasted)
        {
            Healing = healing;
        }

        public HealingMissle(Missle copyMissle, int healing) : base(copyMissle)
        {
            Healing = healing;
        }


    }
}
