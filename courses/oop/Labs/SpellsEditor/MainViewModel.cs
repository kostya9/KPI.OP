using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Spells.Domain;

namespace SpellsEditor
{
    class MainViewModel
    {
        public WallBlockViewModel WallBlocks { get; }
        public SpellsViewModel Spells { get; }

        public MainViewModel()
        {
            WallBlocks = new WallBlockViewModel();
            Spells = new SpellsViewModel();
        }
    }
}
