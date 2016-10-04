using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Spells.Domain
{
    public enum SpinningMissleState
    {
        None = -1, Top, Right, Bottom, Left
    }

    public static class SpinningMissleStateExtensions
    {
        public static SpinningMissleState GetPreviousMissleState(this SpinningMissleState state)
        {
            if (state != SpinningMissleState.Top)
                return state - 1;

            return SpinningMissleState.Left;
        }

        public static SpinningMissleState GetNextMissleState(this SpinningMissleState state)
        {
            if (state != SpinningMissleState.Left)
                return state + 1;

            return SpinningMissleState.Top;
        }
    }
}
