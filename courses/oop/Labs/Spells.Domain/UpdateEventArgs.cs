using System;

namespace Spells.Domain
{
    public class UpdateEventArgs : EventArgs
    {
        public UpdateEventArgs(ValidatePosition validater)
        {
            Validater = validater;
        }

        public ValidatePosition Validater { get; }
    }
}