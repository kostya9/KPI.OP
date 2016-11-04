namespace Spells.Domain
{
    public interface ICollidable
    {
        bool IsDestroyed { get; }
        void Collide(ICollidable other);
    }
}