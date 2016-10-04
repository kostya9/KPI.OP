namespace Spells.Domain
{
    public interface IDamagable
    {
        int Health { get; }
        void Damage(int damage);
    }
}