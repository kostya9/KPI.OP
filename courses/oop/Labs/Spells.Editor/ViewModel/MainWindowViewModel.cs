using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Spells.Editor.ViewModel
{
    internal class MainWindowViewModel : BindableBase
    {
        public SpellsViewModel SpellsViewModel { get; }
        public SaveViewModel SaveViewModel { get; }

        public MainWindowViewModel()
        {
            SpellsViewModel = new SpellsViewModel();
            SaveViewModel = new SaveViewModel();
        }
    }
}
