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

    public delegate void MisslesCollidedHandler(Missle first, Missle second,
    EventArgs args);

    public class MissleMovedHandlerArgs
    {
        public Vector2D PreviousPosition { get; }

        public MissleMovedHandlerArgs(Vector2D previousPosition)
        {
            this.PreviousPosition = previousPosition;
        }
    }

    public class MissleMover
    {
        private readonly ValidatePosition _validater;
        private readonly List<Missle> _missles;
        public event MissleMovedHandler MissleMoved;
        public event MisslesCollidedHandler MisslesCollided;

        public MissleMover(ValidatePosition validater)
        {
            _missles = new List<Missle>();
            this._validater = validater;
        }

        public void AddMissle(Missle missle)
        {
            this._missles.Add(missle);
        }

        public void OnUpdate(SpellsContainer container,
            UpdateEventArgs args)
        {
            MoveMissles();
            CheckForCollision();
        }

        public void MoveMissles()
        {
            foreach (var missle in _missles.ToList())
            {
                var prevPosition = missle.Position;
                missle.UpdatePosition();

                if (!_validater(missle.Position))
                    RemoveMissle(missle);
                else
                    MissleMoved?.Invoke(missle, new MissleMovedHandlerArgs(prevPosition));
            }   
        }

        public void RemoveMissle(Missle missle)
        {
            _missles.Remove(missle);
        }

        private void CheckForCollision()
        {
            Dictionary<Vector2D, Missle> map = new Dictionary<Vector2D, Missle>();

            foreach (var missle in _missles.ToList())
            {
                var position = missle.Position;
                if (map.ContainsKey(position))
                    MisslesCollided?.Invoke(missle, map[position], new EventArgs());
                else
                {
                    map[position] = missle;
                }
            }
        }
    }


}
