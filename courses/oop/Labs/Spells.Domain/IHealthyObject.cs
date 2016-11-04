using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

namespace Spells.Domain
{
    public interface IHealthyObject
    {
        int MaxHitPoints { get; }
        int HitPoints { get; }
    }
}
