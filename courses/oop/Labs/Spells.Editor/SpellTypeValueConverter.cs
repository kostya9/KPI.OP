using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;
using Spells.Editor.Model;

namespace Spells.Editor
{
    class SpellTypeValueConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if(!(value is SpellsType))
                throw new ArgumentException("Provided value is not a spellstype");
            switch ((SpellsType)value)
            {
                case SpellsType.FireBall:
                    return "Fire Ball";
                case SpellsType.HealingBall:
                    return "Healing Ball";
                case SpellsType.SpinningFireBall:
                    return "Spinning Fire Ball";
                default:
                    return "Unknown";
            }
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (!(value is string))
                throw new ArgumentException("Provided value is not a spellstype");
            switch ((string)value)
            {
                case "Fire Ball":
                    return SpellsType.FireBall;
                case "Healing Ball":
                    return SpellsType.HealingBall;
                case "Spinning Fire Ball":
                    return SpellsType.SpinningFireBall;
                default:
                    return SpellsType.FireBall;
            }
        }
    }
}
