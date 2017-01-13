using System.Collections.Generic;
using System.IO;
using System.Windows;
using Newtonsoft.Json;
using Spells.Editor.Model;

namespace Spells.Editor.ViewModel
{
    internal class SaveViewModel : BindableBase
    {
        private string _pathToExportFile;

        public string PathToExportFile
        {
            get { return _pathToExportFile; }
            set { SetProperty(ref _pathToExportFile, value); }
        }

        public ArgumentlessICommand ExportCommand { get; set; }
        public List<SpellModel> Spells { get; set; }

        public SaveViewModel()
        {
            PathToExportFile = "";
            ExportCommand = new ArgumentlessICommand(Export);
        }

        public void Export()
        {
            string directory = null;
            try
            {
                directory = Path.GetDirectoryName(_pathToExportFile);
            }
            catch
            {
                directory = null;
            }
            if (Directory.Exists(directory) == false)
            {
                MessageBox.Show("This directory does not exist", "Error directory not exists", MessageBoxButton.OK,
                    MessageBoxImage.Error);
                return;
            }

            string spellsString = JsonConvert.SerializeObject(Spells);
            try
            {
                File.WriteAllText(_pathToExportFile, spellsString);
            }
            catch
            {
                MessageBox.Show("Something bad happened while writing to file", "Error", MessageBoxButton.OK,
    MessageBoxImage.Error);
                return;
            }
            MessageBox.Show("The spells were exported", "Success!", MessageBoxButton.OK,
    MessageBoxImage.Information);

        }
    }
}