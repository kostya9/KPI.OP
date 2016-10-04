using System;

namespace Spells.Domain
{
    public class CooldownException : Exception
    {
        public CooldownException() : base("This spell was already castes and is on cooldown")
        {
            
        }
    }
}