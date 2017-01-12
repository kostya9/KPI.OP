using System.Collections.ObjectModel;
using System.Dynamic;
using System.Linq;
using System.Windows;
using Spells.Editor.Model;

namespace Spells.Editor.ViewModel
{
    internal class SpellsViewModel : BindableBase
    {
        private ObservableCollection<SpellModel> _spellList;
        private SpellModel _selectedSpell;
        private SpellModel _addingSpell;
        private SpellModel _changingSpell;

        public ObservableCollection<SpellModel> SpellList
        {
            get { return _spellList; }
            set { SetProperty(ref _spellList, value); }
        }

        public SpellModel SelectedSpell
        {
            get { return _selectedSpell; }
            set
            {
                SetProperty(ref _selectedSpell, value);
                ChangingSpell = SelectedSpell;
            }
        }

        public SpellModel AddingSpell
        {
            get { return _addingSpell; }
            set
            {
                SetProperty(ref _addingSpell, value);
                AddingSpell.Coordinates.PropertyChanged += (p, e) =>
                {
                    AddCommand.RaiseCanExecuteChanged();
                };
            }
        }

        public SpellModel ChangingSpell
        {
            get { return _changingSpell; }
            set
            {
                SetProperty(ref _changingSpell,
                    value != null
                        ? new SpellModel
                        {
                            Coordinates = new Vector2D(value.Coordinates.X, value.Coordinates.Y),
                            SpellType = value.SpellType
                        }
                        : null);
                if(ChangingSpell != null)
                ChangingSpell.Coordinates.PropertyChanged += (p, e) =>
                {
                    ChangeCommand.RaiseCanExecuteChanged();
                };
            }
        }

        public SpellsViewModel()
        {
            SpellList = new ObservableCollection<SpellModel> {new SpellModel()};
            AddingSpell = new SpellModel();
            AddCommand = new GenericICommand<object>(Add, CanAdd);
            DeleteCommand = new GenericICommand<SpellModel>(Delete);
            ChangeCommand = new GenericICommand<object>(Change, CanChange);


        }

        public GenericICommand<object> AddCommand { get; set; }
        public GenericICommand<object> ChangeCommand { get; set; }

        public GenericICommand<SpellModel> DeleteCommand { get; set; }

        public void Add(object arg)
        {
            SpellList.Add(AddingSpell);
            AddingSpell = new SpellModel();
            ChangeCommand.RaiseCanExecuteChanged();
            AddCommand.RaiseCanExecuteChanged();
        }

        public bool CanAdd(object arg)
        {
            return !SpellList.Any(s => s.Coordinates.Equals(AddingSpell.Coordinates));
        }

        public void Delete(SpellModel model)
        {
            MessageBoxResult result = MessageBox.Show("Are you sure about deleting this?", "Delete confirmation",
                MessageBoxButton.YesNo);
            if (result == MessageBoxResult.No)
                return;
            SpellList.Remove(model);
            AddCommand.RaiseCanExecuteChanged();
            ChangeCommand.RaiseCanExecuteChanged();
        }

        public void Change(object arg)
        {
            _selectedSpell.Coordinates = _changingSpell.Coordinates;
            _selectedSpell.SpellType = _changingSpell.SpellType;
            AddCommand.RaiseCanExecuteChanged();
            ChangeCommand.RaiseCanExecuteChanged();
        }

        public bool CanChange(object arg)
        {
            return _changingSpell != null && SpellList.All(s => s.Coordinates != ChangingSpell?.Coordinates);
        }


    }
}