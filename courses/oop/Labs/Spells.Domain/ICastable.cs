
namespace Spells.Domain
{
    public interface ICastable
    {
        bool CanCast();

        Missle Cast(Vector2D position,
            Vector2D direction);
    }
}