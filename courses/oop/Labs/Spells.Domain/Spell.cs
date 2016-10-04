using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Spells.Domain
{
    public class Spell : ICastable
    {

        public int Id {get; }
        public string Name { get; }
        public int MissleSpeed { get; }
        public int Damage { get;}
        public int Volume { get; }
        public TimeSpan Cooldown { get; }
        public string Sound { get; }

        private TimeSpan _lastCasted;
        private readonly Stream _output;
       

        public Spell(int id,
            string name,
            int missleSpeed,
            int damage,
            int volume,
            TimeSpan cooldown,
            string sound,
            Stream output)
        {
            Id = id;
            Name = name;
            MissleSpeed = missleSpeed;
            Damage = damage;
            Volume = volume;
            Cooldown = cooldown;
            Sound = sound;
            _output = output;
        }

        public virtual Missle Cast(Vector2D position, Vector2D direction)
        {
            var canCast = CanCast();
            if (!canCast)
                throw new CooldownException();
            var timeNow = TimeHelper.GetCurrentTime();

            _lastCasted = timeNow;

            var writer = new StreamWriter(_output);
            writer.WriteLine("Spell casted : {0}.\n Shouts {1}", Name, Sound);

            return new Missle(this, position, direction, timeNow);
        }

        public bool CanCast()
        {
            return _lastCasted + Cooldown < TimeHelper.GetCurrentTime();
        }
    }
}
