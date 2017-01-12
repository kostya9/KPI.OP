using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Spells.Editor.Views
{
    /// <summary>
    /// Interaction logic for SpellsView.xaml
    /// </summary>
    public partial class SpellsView : UserControl
    {
        public SpellsView()
        {
            InitializeComponent();
        }

        private void NumberValidation(object sender, TextCompositionEventArgs e)
        {
            var textBox = (TextBox)sender;
            var text = textBox.Text.Insert(textBox.CaretIndex, e.Text);
            Regex regex = new Regex("^-?[0-9]+$");
            if (text.Length == 1 && text[0] == '-')
                e.Handled = false;
            else
                e.Handled = !regex.IsMatch(text);
        }
    }
}
