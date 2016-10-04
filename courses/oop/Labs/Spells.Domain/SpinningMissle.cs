using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Win32.SafeHandles;

namespace Spells.Domain
{
    class SpinningMissle : Missle
    {
        private const int _radius = 1;
        private SpinningMissleState _spinningMissleState;

        public SpinningMissle(Spell castedSpell,
            Vector2D position,
            Vector2D direction,
            TimeSpan timeCasted) : base(castedSpell, position,
            direction, timeCasted)
        {
            _spinningMissleState = SpinningMissleState.None;
        }

        public SpinningMissle(Missle copyMissle) : base(copyMissle)
        {
            _spinningMissleState = SpinningMissleState.None;
        }

        private Vector2D GetNextSpinningDirection(SpinningMissleState state)
        {
            switch (state)
            {
                case SpinningMissleState.Top:
                    return new Vector2D(0, 1);
                case SpinningMissleState.Right:
                    return new Vector2D(1, 0);
                case SpinningMissleState.Bottom:
                    return new Vector2D(0, -1);
                case SpinningMissleState.Left:
                    return new Vector2D(-1, 0);
                case SpinningMissleState.None:
                    return new Vector2D(0, 0);
                default:
                    throw new ArgumentOutOfRangeException();
            }
        }

        private Vector2D GetPreviousSpinningDirection()
        {
            var state = _spinningMissleState.GetPreviousMissleState();
            return GetNextSpinningDirection(state);
        }

        private Vector2D GetNextSpinningDirection()
        {
            return GetNextSpinningDirection(_spinningMissleState);
        }

        public override void UpdatePosition()
        {
            base.UpdatePosition();

            var wasNone = _spinningMissleState == SpinningMissleState.None;
            _spinningMissleState = _spinningMissleState.GetNextMissleState();

            if(!wasNone)
                Position -= GetPreviousSpinningDirection();
            Position += GetNextSpinningDirection();
        }
    }

}
