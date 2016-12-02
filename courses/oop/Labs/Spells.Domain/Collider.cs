using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.ExceptionServices;
using System.Text;
using System.Threading.Tasks;

namespace Spells.Domain
{
    internal class Collider
    {
        private readonly MissleMover _missleMover;
        private readonly List<Missle> _wasBrokenIntoPieces;
        private readonly WallStore _store;

        public Collider(MissleMover missleMover,
            WallStore store)
        {
            _missleMover = missleMover;
            _store = store;
            _wasBrokenIntoPieces = new List<Missle>();
            AddMissleMoverSubscriptions();
        }

        private void AddMissleMoverSubscriptions()
        {
            _missleMover.MisslesCollided += (mFirst,
                mSecond,
                e) => Debug.WriteLine("Collision!");

            _missleMover.MisslesCollided += (missle,
                    collision,
                    e) =>
                {
                    var healing = missle as HealingMissle;
                    if (healing == null)
                        return;
                    var block = collision as WallBlock;
                    if (block == null)
                        return;
                    block.ChangeHitpoints(w => w.HitPoints + healing.Healing, (w) => Debug.WriteLine("Could not heal"));
                    healing.Collide(block);
                };

            _missleMover.MisslesCollided += (mFirst,
                    mSecond,
                    e) =>
            {
                if (mFirst.IsDestroyed || mSecond.IsDestroyed)
                    return;
                mFirst.Collide(mSecond);
                mSecond.Collide(mFirst);
            };

            _missleMover.MisslesCollided += delegate (Missle first,
                ICollidable second,
                EventArgs e)
            {
                var otherMissle = second as Missle;
                if (otherMissle == null || _wasBrokenIntoPieces.Contains(first) || _wasBrokenIntoPieces.Contains(second))
                {
                    _wasBrokenIntoPieces.Remove(first);
                    _wasBrokenIntoPieces.Remove(otherMissle);
                    return;
                }

                Missle m1 = new Missle(first.CastedSpell, first.Position, new Vector2D(1, 1),
                    TimeHelper.GetCurrentTime());
                Missle m2 = new Missle(first.CastedSpell, first.Position, new Vector2D(-1, -1),
                    TimeHelper.GetCurrentTime());
                Missle m3 = new Missle(otherMissle.CastedSpell, first.Position, new Vector2D(1, -1),
                    TimeHelper.GetCurrentTime());
                Missle m4 = new Missle(otherMissle.CastedSpell, first.Position, new Vector2D(-1, 1),
                    TimeHelper.GetCurrentTime());
                _missleMover.AddMissle(m1);
                _missleMover.AddMissle(m2);
                _missleMover.AddMissle(m3);
                _missleMover.AddMissle(m4);
                _wasBrokenIntoPieces.AddRange(new [] {m1, m2, m3, m4});
            };
        }
    }
}
