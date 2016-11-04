using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Spells.Domain
{

    public delegate void SpellCooldownZeroHandler(ICastable sender,
        SpellCooldownZeroEventArgs args);

    public class SpellsContainer
    {

        private event SpellCooldownZeroHandler SpellCooldownZero;

        private readonly Dictionary<ICastable, Vector2D> _spells;
        private readonly MissleMover _missleMover;
        private readonly ValidatePosition _validater;
        private readonly WallStore _store;

        public SpellsContainer(ValidatePosition validater)
        {
            _spells = new Dictionary<ICastable, Vector2D>();
            _missleMover = new MissleMover(validater);
            _validater = validater;
            _store = new WallStore();
            _missleMover.MisslesCollided += MisslesCollisionHandler;
        }

        public IHealthyObject GetHealthyObjectAt(Vector2D position)
        {
            return _store.GetWallAt(position);
        }

        public void SubscribeToMissleMove(MissleMovedHandler handler)
        {
            this._missleMover.MissleMoved += handler;
        }

        public void UnsubscribeToMissleMove(MissleMovedHandler handler)
        {
            this._missleMover.MissleMoved -= handler;
        }

        public void SubscribeToCooldownZero(SpellCooldownZeroHandler handler)
        {
            this.SpellCooldownZero += handler;
        }

        public void UnsubscribeToCooldownZero(SpellCooldownZeroHandler handler)
        {
            this.SpellCooldownZero -= handler;
        }

        public void AddSpell(ICastable spell,
            Vector2D position)
        {
            if (spell == null)
                throw new ArgumentNullException();
            _spells[spell] = position;
        }

        public void AddWall(Vector2D position)
        {
            _store.CreateWall(position);
        }

        public void CheckSpellCooldowns()
        {
            foreach (var spellAndPosition in _spells)
            {
                if (spellAndPosition.Key.CanCast())
                    SpellCooldownZero?.Invoke(spellAndPosition.Key, new SpellCooldownZeroEventArgs(spellAndPosition.Value));
            }
        }

        public void Update()
        {
            CheckSpellCooldowns();
            _missleMover.Move(_store);
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

        public void CastSpell(ICastable spell, Vector2D direction)
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

        private void MisslesCollisionHandler(Missle first,
            ICollidable second,
            EventArgs args)
        {
            if(first.IsDestroyed || second.IsDestroyed)
                return;
            first.Collide(second);
            second.Collide(first);
            Debug.WriteLine("Collision!");

            var otherMissle = second as Missle;
            if (otherMissle == null || first.IsCollided || otherMissle.IsCollided)
            {
                return;
            }

            Missle m1 = new Missle(first.CastedSpell, first.Position, new Vector2D(1, 1), TimeHelper.GetCurrentTime(), true);
            Missle m2 = new Missle(first.CastedSpell, first.Position, new Vector2D(-1, -1), TimeHelper.GetCurrentTime(), true);
            Missle m3 = new Missle(otherMissle.CastedSpell, first.Position, new Vector2D(1, -1), TimeHelper.GetCurrentTime(), true);
            Missle m4 = new Missle(otherMissle.CastedSpell, first.Position, new Vector2D(-1, 1), TimeHelper.GetCurrentTime(), true);
            _missleMover.AddMissle(m1);
            _missleMover.AddMissle(m2);
            _missleMover.AddMissle(m3);
            _missleMover.AddMissle(m4);
        }
    }

}
