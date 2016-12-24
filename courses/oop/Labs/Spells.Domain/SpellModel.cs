using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Spells.Domain
{
    public class SpellModel
    {
        public Spells SpellClass { get; set; }
        public Vector2D Position { get; set; }
    }
}
