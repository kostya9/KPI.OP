using System;

namespace Spells.Domain
{
    public class CooldownException : Exception
    {
        public CooldownExceptionArgs Args { get; }

        public CooldownException(CooldownExceptionArgs args) : base("This spell was already castes and is on cooldown")
        {
            Args = args;
        }
    }
}