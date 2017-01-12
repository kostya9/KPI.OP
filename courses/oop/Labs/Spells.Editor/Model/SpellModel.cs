using Spells.Editor.ViewModel;

namespace Spells.Editor.Model
{
    internal class SpellModel : BindableBase
    {
        private SpellsType _spellType;
        private Vector2D _coordinates;

        public SpellsType SpellType
        {
            get { return _spellType; }
            set { SetProperty(ref _spellType, value); }
        }

        public Vector2D Coordinates
        {
            get { return _coordinates; }
            set { SetProperty(ref _coordinates, value); }
        }

        public SpellModel()
        {
            Coordinates = new Vector2D(0, 0);
        }
    }
}