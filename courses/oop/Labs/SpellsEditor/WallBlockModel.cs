using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Spells.Domain;

namespace SpellsEditor
{
    class WallBlockViewModel : ObservableCollection<WallBlockModel>
    {
        public void AddWallBlock(Vector2D position,
            int quantity,
            int maxHealth)
        {
            if(quantity <= 0)
                throw new ArgumentException("Quantity should be more than zero");
            if(maxHealth <= 0)
                throw new ArgumentException("Max health should be more than zero");
            Add(new WallBlockModel
            {
                MaxHealth = maxHealth,
                Position = position,
                Quantity = quantity
            });
        }

        public void DeleteWallBlock(WallBlockModel model)
        {
            Remove(model);
        }
    }
}
