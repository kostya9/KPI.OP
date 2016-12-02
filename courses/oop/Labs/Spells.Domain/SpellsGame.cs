using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Spells.Domain
{
    public class SpellsGame
    {
        public SpellsContainer SpellsContainer { get; }
        private readonly MissleMover _missleMover;
        public WallStore WallStore { get; }
        private Collider _collider;
        public event SpellCooldownZeroHandler SpellCooldownZero
        {
            add { SpellsContainer.SpellCooldownZero += value; }
            remove { SpellsContainer.SpellCooldownZero -= value; }
        }

        public event MissleMovedHandler MissleMoved
        {
            add { _missleMover.MissleMoved += value; }
            remove { _missleMover.MissleMoved -= value; }
        }

        public SpellsGame(ValidatePosition validater)
        {
            SpellsContainer = new SpellsContainer();
            _missleMover = new MissleMover(validater);
            WallStore = new WallStore();
            _collider = new Collider(_missleMover, WallStore);

            SpellsContainer.SpellCasted += (s,
                e) => _missleMover.AddMissle(e.Missle);
        }



        public void Update()
        {
            SpellsContainer.CheckSpellCooldowns();
            _missleMover.Move(WallStore);
        }
    }
}
