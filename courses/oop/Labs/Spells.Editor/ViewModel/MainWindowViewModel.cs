using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using Microsoft.Win32;
using Newtonsoft.Json;
using Spells.Editor.Model;

namespace Spells.Editor.ViewModel
{
    internal class MainWindowViewModel : BindableBase
    {
        private SpellsViewModel _spellsViewModel;

        public SpellsViewModel
            SpellsViewModel
        {
            get { return _spellsViewModel; }
            set
            {
                SetProperty(ref _spellsViewModel, value);
            }
        }

        public SaveViewModel SaveViewModel { get; set; }

        public GenericICommand<object> ExitCommand { get; set; }
        public GenericICommand<object> ImportCommand { get; set; }

        public MainWindowViewModel()
        {
            SpellsViewModel = new SpellsViewModel();
            SaveViewModel = new SaveViewModel();
            ExitCommand = new GenericICommand<object>(Exit);
            ImportCommand = new GenericICommand<object>(Import);
        }

        public void Exit(object arg)
        {
            Application.Current.Shutdown();
        }

        public void Import(object arg)
        {
            OpenFileDialog fileDialog = new OpenFileDialog();
            if (fileDialog.ShowDialog() == true)
            {
                var ext = Path.GetExtension(fileDialog.FileName);
                if (ext != ".json")
                {
                    MessageBox.Show("Incorrect format. Need json.","Error file format",MessageBoxButton.OK, MessageBoxImage.Error);
                    return;
                }

                var contents = File.ReadAllText(fileDialog.FileName);
                List<SpellModel> spells;
                try
                {
                    spells = JsonConvert.DeserializeObject<List<SpellModel>>(contents);
                }
                catch
                {
                    MessageBox.Show("Something bad happened while reading the file. Is the file a correct json file?", "Error", MessageBoxButton.OK,
MessageBoxImage.Error);
                    return;
                }
                if (spells.Count == 0)
                    return;
                SpellsViewModel = new SpellsViewModel();
                SpellsViewModel.SpellList = new ObservableCollection<SpellModel>();
                foreach (var spell in spells)
                {
                    SpellsViewModel.SpellList.Add(spell);
                }
            }
        }
    }
}
