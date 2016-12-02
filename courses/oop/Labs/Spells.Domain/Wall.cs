namespace Spells.Domain
{
    internal class Wall : ICollidable, IHealthyObject
    {
        public int MaxHitPoints => 10;
        private int _hitPoints;

        public int HitPoints => _hitPoints;

        public Wall()
        {
            _hitPoints = MaxHitPoints;
        }
        public bool IsCollided => _hitPoints < 10;
        public bool IsDestroyed => _hitPoints == 0;

        public void Collide(ICollidable other)
        {
            _hitPoints = _hitPoints > 0 ? _hitPoints - 1 : 0;
        }
    }
}