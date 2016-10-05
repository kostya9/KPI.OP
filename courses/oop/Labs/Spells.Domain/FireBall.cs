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
        protected FireBall(Spells id) : base((int)id, id.ToString(), 1, 1, 1, TimeSpan.FromSeconds(2), "ShhhBoom")
        {
            
        }

        public FireBall() :
            this(Spells.FireBall)
        {

        }
    }
}
