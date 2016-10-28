using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Spells.Domain
{
    public delegate bool ValidatePosition(Vector2D position);

    public delegate void MissleMovedHandler(Missle sender,
    MissleMovedHandlerArgs args);

    public class MissleMovedHandlerArgs
    {
        public Vector2D PreviousPosition { get; }

        public MissleMovedHandlerArgs(Vector2D previousPosition)
        {
            this.PreviousPosition = previousPosition;
        }
    }

    class MissleMover
    {
        private ValidatePosition _validater;
        private List<Missle> _missles;
        public event MissleMovedHandler MissleMoved;

        public MissleMover(ValidatePosition validater)
        {
            _missles = new List<Missle>();
            this._validater = validater;
        }

        public void AddMissle(Missle missle)
        {
            this._missles.Add(missle);
        }

        public void MoveMissles()
        {
            foreach (var missle in _missles.ToList())
            {
                var prevPosition = missle.Position;
                missle.UpdatePosition();

                if (!_validater(missle.Position))
                    _missles.Remove(missle);
                else
                    MissleMoved?.Invoke(missle, new MissleMovedHandlerArgs(prevPosition));
            }
        }
    }
}
