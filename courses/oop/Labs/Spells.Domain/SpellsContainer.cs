using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Spells.Domain;

namespace Spells.Domain
{

    public delegate void SpellCooldownZeroHandler(ICastable sender,
        SpellCooldownZeroEventArgs args);

    internal delegate void SpellCastedEventHandler(ICastable sender,
    SpellCastedEventArgs args);

    public class SpellsContainer
    {

        internal event SpellCooldownZeroHandler SpellCooldownZero;

        private readonly Dictionary<ICastable, Vector2D> _spells;

        internal event SpellCastedEventHandler SpellCasted;

        internal SpellsContainer()
        {
            _spells = new Dictionary<ICastable, Vector2D>();
        }

        public void CastSpell(ICastable spell,
            Vector2D direction)
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
            var missle = spell.Cast(position, direction);
            OnSpellCasted(spell, missle);
        }

        public void AddSpell(ICastable spell,
            Vector2D position)
        {
            if (spell == null)
                throw new ArgumentNullException();
            _spells[spell] = position;
        }

        internal void CheckSpellCooldowns()
        {
            foreach (var spellAndPosition in _spells)
            {
                if (spellAndPosition.Key.CanCast())
                    SpellCooldownZero?.Invoke(spellAndPosition.Key,
                        new SpellCooldownZeroEventArgs(spellAndPosition.Value));
            }
        }

        internal void CastAllSpellsToRandomDirection()
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

        protected virtual void OnSpellCasted(ICastable sender, Missle missle)
        {
            SpellCasted?.Invoke(sender, new SpellCastedEventArgs {Missle = missle});
        }
    }
}

public class SpellCastedEventArgs: EventArgs
{
    public Missle Missle { get; set; }
}
