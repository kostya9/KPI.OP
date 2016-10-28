using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Spells.Domain
{
    public class SpellsContainer
    {
        private readonly Dictionary<ICastable, Vector2D> _spells = new Dictionary<ICastable, Vector2D>();
        private readonly MissleMover _missleMover;

        public SpellsContainer(ValidatePosition validater)
        {
            _missleMover = new MissleMover(validater);
        }

        public void SubscribeToMissleMove(MissleMovedHandler handler)
        {
            this._missleMover.MissleMoved += handler;
        }

        public void UnsubscribeToMissleMove(MissleMovedHandler handler)
        {
            this._missleMover.MissleMoved -= handler;
        }

        public void AddSpell(ICastable spell,
            Vector2D position)
        {
            if (spell == null)
                throw new ArgumentNullException();
            _spells[spell] = position;
        }

        public void UpdateSpells()
        {
            _missleMover.MoveMissles();
        }

        public void CastAllSpellsToRandomDirection()
        {
            var r = new Random();
            foreach (var spell in _spells)
            {
                var x = 1 - r.Next(3);
                var direction = x != 0
                    ? new Vector2D(x, 0)
                    : new Vector2D(0, 1 - r.Next(3)); 
                CastSpell(spell.Key, direction);
            }
        }

        private void CastSpell(ICastable spell, Vector2D direction)
        {
            if (spell == null)
                throw new ArgumentNullException();
            Vector2D position;
            try
            {
                position = _spells[spell];
            }
            catch (KeyNotFoundException e)
            {
                Debug.WriteLine("Could not find a spell in the dictionary");
                return;
            }
            _missleMover.AddMissle(spell.Cast(position, direction));
        }
    }
}
