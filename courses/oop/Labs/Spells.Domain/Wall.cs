using System;
using System.Runtime.Serialization;
using System.Xml.Serialization;

namespace Spells.Domain
{
    [DataContract]
    [Serializable]
    public class Wall : ICollidable, IHealthyObject, IComparable
    {
        public int MaxHitPoints { get; }

        
        private int _hitPoints;
        [DataMember]
        [XmlAttribute]
        public int HitPoints
        {
            get { return _hitPoints; }
            set
            {
                if(value > MaxHitPoints)
                    throw new ArgumentException();
                _hitPoints = value;
            }
        }

        public Wall()
        {
            MaxHitPoints = 5;
            _hitPoints = MaxHitPoints;
        }

        public Wall(int maxHitpoints)
        {
            if (maxHitpoints <= 0) throw new ArgumentOutOfRangeException(nameof(maxHitpoints));
            MaxHitPoints = maxHitpoints;
            _hitPoints = MaxHitPoints;
        }

        public bool IsCollided => _hitPoints < MaxHitPoints;
        public bool IsDestroyed => _hitPoints == 0;

        public void Collide(ICollidable other)
        {
            _hitPoints = _hitPoints > 0 ? _hitPoints - 1 : 0;
        }

        public int CompareTo(object obj)
        {
            var wall = obj as Wall;

            if (wall == null)
                return -1;

            return HitPoints.CompareTo(wall.HitPoints);
        }
    }
}