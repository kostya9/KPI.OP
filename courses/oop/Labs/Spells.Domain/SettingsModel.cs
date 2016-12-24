using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Spells.Domain
{
    class SettingsModel
    {
        public List<WallBlockModel> WallModels { get; set; }
        public List<SpellModel> SpellModels { get; set; }
    }
}
