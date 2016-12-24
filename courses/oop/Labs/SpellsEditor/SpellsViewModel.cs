using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Spells.Domain;
using SpellsType = Spells.Domain.Spells;

namespace SpellsEditor
{
    class SpellsViewModel : ObservableCollection<SpellModel>
    {
        public void AddSpell(Vector2D position,
            SpellsType spellType)
        {
            if(!Enum.IsDefined(typeof(SpellsType), spellType))
                throw new ArgumentException("Incorrect spell type");

            Add(new SpellModel
            {
                Position = position,
                SpellClass = spellType
            });
        }

        public void RemoveSpell(SpellModel model)
        {
            Remove(model);
        }
    }
}
