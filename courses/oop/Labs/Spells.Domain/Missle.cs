using System;

namespace Spells.Domain
{
    public class Missle : ICollidable
    {
        private readonly TimeSpan _timeCasted;

        public Missle(Spell castedSpell,
            Vector2D position,
            Vector2D direction,
            TimeSpan timeCasted)
        {
            if (castedSpell == null)
                throw new ArgumentNullException();
            CastedSpell = castedSpell;
            Position = position;
            Direction = direction;
            _timeCasted = timeCasted;
        }

        public Missle(Spell castedSpell,
            Vector2D position,
            Vector2D direction,
            TimeSpan timeCasted,
            bool isCollided) : this(castedSpell, position, direction, timeCasted)
        {
            IsCollided = isCollided;
        }

        public Missle(Missle copyMissle)
        {
            if (copyMissle == null)
                throw new ArgumentNullException();
            CastedSpell = copyMissle.CastedSpell;
            Position = copyMissle.Position;
            Direction = copyMissle.Direction;
            _timeCasted = copyMissle._timeCasted;
        }

        public Spell CastedSpell { get; }

        public Vector2D Position { get; protected set; }
        protected Vector2D Direction { get; private set; }
        public bool IsCollided { get; }
        public bool IsDestroyed => Direction == new Vector2D(0, 0);

        public void Collide(ICollidable other)
        {
            Collide();
        }

        public void Collide()
        {
            Direction = new Vector2D(0, 0);
        }

        public virtual void UpdatePosition()
        {
            Position += Direction;
        }
    }
}