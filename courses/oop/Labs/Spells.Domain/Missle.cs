using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Spells.Domain
{
    public class Missle
    {
        public Missle(Spell castedSpell, Vector2D position,
            Vector2D direction,
            TimeSpan timeCasted)
        {
            CastedSpell = castedSpell;
            Position = position;
            _direction = direction;
            _timeCasted = timeCasted;
        }

        public Missle(Missle copyMissle)
        {
            this.CastedSpell = copyMissle.CastedSpell;
            this.Position = copyMissle.Position;
            this._direction = copyMissle._direction;
            this._timeCasted = copyMissle._timeCasted;
        }

        public Spell CastedSpell { get; }
        public Vector2D Position { get; protected set; }
        protected readonly Vector2D _direction;
        private TimeSpan _timeCasted;

        public virtual void UpdatePosition()
        {
            Position += _direction;
        }
    }
}
