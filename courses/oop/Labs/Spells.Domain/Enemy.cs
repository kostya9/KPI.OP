namespace Spells.Domain
{
    public class Enemy : IDamagable
    {
        public Enemy(Vector2D position,
            int volume,
            int health)
        {
            Position = position;
            Volume = volume;
            Health = health;
        }

        public Vector2D Position { get; private set; }
        public int Volume { get; private set; }
        public int Health { get; private set; }

        public void Damage(int damage)
        {
            this.Health -= damage;

            if (Health < 0)
                Health = 0;
        }
    }
}