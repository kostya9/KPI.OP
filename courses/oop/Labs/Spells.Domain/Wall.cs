using System;

namespace Spells.Domain
{
    internal class Wall : ICollidable, IHealthyObject, IComparable
    {
        public int MaxHitPoints => 5;
        private int _hitPoints;

        public int HitPoints => _hitPoints;

        public Wall()
        {
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