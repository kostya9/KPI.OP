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

        private event SpellCooldownZeroHandler _spellCooldownZero;

        private delegate void UpdateHandler(SpellsContainer container,
            UpdateEventArgs args);

        private readonly Dictionary<ICastable, Vector2D> _spells;
        private readonly MissleMover _missleMover;
        private event UpdateHandler _update;
        private readonly ValidatePosition _validater;

        public SpellsContainer(ValidatePosition validater)
        {
            _spells = new Dictionary<ICastable, Vector2D>();
            _missleMover = new MissleMover(validater);
            _update += _missleMover.OnUpdate;
            _validater = validater;
            _missleMover.MisslesCollided += MisslesCollisionHandler;
        }

        public void StartMeasuringTime()
        {
            TimeHelper.Start();
        }

        public void StopMeasuringTime()
        {
            TimeHelper.Stop();
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
            this._spellCooldownZero += handler;
        }

        public void UnsubscribeToCooldownZero(SpellCooldownZeroHandler handler)
        {
            this._spellCooldownZero -= handler;
        }

        public void AddSpell(ICastable spell,
            Vector2D position)
        {
            if (spell == null)
                throw new ArgumentNullException();
            _spells[spell] = position;
        }

        public void CheckSpellCooldowns()
        {
            
        }

        public void Update()
        {
            foreach (var spellAndPosition in _spells)
            {
                if(spellAndPosition.Key.CanCast())
                    _spellCooldownZero?.Invoke(spellAndPosition.Key, new SpellCooldownZeroEventArgs(spellAndPosition.Value));
            }
            _update?.Invoke(this, new UpdateEventArgs(_validater));
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
            Missle second,
            EventArgs args)
        {
            this._missleMover.RemoveMissle(first);
            this._missleMover.RemoveMissle(second);
            Debug.WriteLine("Collision!");
            if (first.IsCollided || second.IsCollided)
            {
                return;
            }

            Missle m1 = new Missle(first.CastedSpell, first.Position, new Vector2D(1, 1),TimeHelper.GetCurrentTime(), true);
            Missle m2 = new Missle(first.CastedSpell, first.Position, new Vector2D(-1, -1), TimeHelper.GetCurrentTime(), true);
            Missle m3 = new Missle(second.CastedSpell, first.Position, new Vector2D(1, -1), TimeHelper.GetCurrentTime(), true);
            Missle m4 = new Missle(second.CastedSpell, first.Position, new Vector2D(-1, 1), TimeHelper.GetCurrentTime(), true);
            _missleMover.AddMissle(m1);
            _missleMover.AddMissle(m2);
            _missleMover.AddMissle(m3);
            _missleMover.AddMissle(m4);
        }
    }

}
