using System;

namespace Spells.Domain
{
    public class SpellCooldownZeroEventArgs : EventArgs
    {
        public SpellCooldownZeroEventArgs(Vector2D position)
        {
            Position = position;
        }

        public Vector2D Position { get; }
    }
}