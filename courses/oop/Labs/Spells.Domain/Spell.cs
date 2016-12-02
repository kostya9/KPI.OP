using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Spells.Domain
{
    public abstract class Spell : ICastable
    {

        public int Id {get; }
        public string Name { get; }
        public int MissleSpeed { get; }
        public int Damage { get;}

        private int _volume;
        public int Volume {
            get { return _volume; }
            set {
                if (value <= 0)
                    throw new ArgumentOutOfRangeException();
                _volume = value;
            }
        }
        public TimeSpan Cooldown { get; }
        public string Sound { get; }

        private TimeSpan _lastCasted;


        protected Spell(int id,
            string name,
            int missleSpeed,
            int damage,
            int volume,
            TimeSpan cooldown,
            string sound)
        {
            Id = id;
            Name = name;
            MissleSpeed = missleSpeed;
            Damage = damage;
            Volume = volume;
            Cooldown = cooldown;
            Sound = sound;
            _lastCasted = new TimeSpan(0, 0, 0, 0, 0);
        }

        public virtual Missle Cast(Vector2D position, Vector2D direction)
        {
            var canCast = CanCast();
            var timeNow = TimeHelper.GetCurrentTime();
            if (!canCast)
                throw new CooldownException(new CooldownExceptionArgs(direction, position, this, Cooldown - (timeNow - _lastCasted)));

            _lastCasted = timeNow;

            Debug.WriteLine($"Spell casted : {Name}\n Shouts {Sound}");
            return new Missle(this, position, direction, timeNow);
        }

        public bool CanCast()
        {
            if(_lastCasted == new TimeSpan(0, 0, 0, 0, 0))
                return true;
            return _lastCasted + Cooldown < TimeHelper.GetCurrentTime();
        }
    }
}
