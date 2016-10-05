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
        private readonly List<Missle> _missles = new List<Missle>();
        public IList<Missle> Missles => _missles.AsReadOnly();

        public void AddSpell(ICastable spell,
            Vector2D position)
        {
            _spells[spell] = position;
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

        public void RemoveMissle(Missle missle)
        {
            _missles.Remove(missle);
        }

        private void CastSpell(ICastable spell, Vector2D direction)
        {
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
            _missles.Add(spell.Cast(position, direction));
        }
    }
}
