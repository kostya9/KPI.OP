using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Spells.Domain
{
    public class FireBall : Spell
    {
        public FireBall(Stream output)
            : base((int) Spells.FireBall, nameof(FireBall), 1, 1, 1, TimeSpan.FromSeconds(2), "ShhhBoom", output)
        {
            
        }
    }
}
