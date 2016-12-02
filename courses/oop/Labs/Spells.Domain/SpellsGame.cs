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

            AddMissleMoverSubscriptions();
            SpellsContainer.SpellCasted += (s,
                e) => _missleMover.AddMissle(e.Missle);
        }

        private void AddMissleMoverSubscriptions()
        {
            _missleMover.MisslesCollided += (mFirst,
                mSecond,
                e) => Debug.WriteLine("Collision!");

            _missleMover.MisslesCollided += (mFirst,
                    mSecond,
                    e) =>
                {
                    if (mFirst.IsDestroyed || mSecond.IsDestroyed)
                        return;
                    mFirst.Collide(mSecond);
                    mSecond.Collide(mFirst);
                };

            _missleMover.MisslesCollided += delegate(Missle first,
                ICollidable second,
                EventArgs e)
            {
                var otherMissle = second as Missle;
                if (otherMissle == null || !first.ShouldBreakIntoPieces || !otherMissle.ShouldBreakIntoPieces)
                {
                    return;
                }

                Missle m1 = new Missle(first.CastedSpell, first.Position, new Vector2D(1, 1),
                    TimeHelper.GetCurrentTime(), true);
                Missle m2 = new Missle(first.CastedSpell, first.Position, new Vector2D(-1, -1),
                    TimeHelper.GetCurrentTime(), true);
                Missle m3 = new Missle(otherMissle.CastedSpell, first.Position, new Vector2D(1, -1),
                    TimeHelper.GetCurrentTime(), true);
                Missle m4 = new Missle(otherMissle.CastedSpell, first.Position, new Vector2D(-1, 1),
                    TimeHelper.GetCurrentTime(), true);
                _missleMover.AddMissle(m1);
                _missleMover.AddMissle(m2);
                _missleMover.AddMissle(m3);
                _missleMover.AddMissle(m4);
            };
        }

        public void Update()
        {
            SpellsContainer.CheckSpellCooldowns();
            _missleMover.Move(WallStore);
        }
    }
}
