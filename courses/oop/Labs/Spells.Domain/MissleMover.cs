using System;
using System.Collections.Generic;
using System.Linq;

namespace Spells.Domain
{
    public delegate bool ValidatePosition(Vector2D position);

    public delegate void MissleMovedHandler(Missle sender,
        MissleMovedHandlerArgs args);

    public delegate void MisslesCollidedHandler(Missle missle,
        ICollidable collision,
        EventArgs args);

    public class MissleMovedHandlerArgs
    {
        public Vector2D PreviousPosition { get; }

        public MissleMovedHandlerArgs(Vector2D previousPosition)
        {
            PreviousPosition = previousPosition;
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
            _validater = validater;
        }

        public void AddMissle(Missle missle)
        {
            _missles.Add(missle);
        }

        public void Move(WallStore store)
        {
            MoveMissles();
            CheckForCollision(store);
        }

        private void MoveMissles()
        {
            foreach (var missle in _missles.ToList())
            {
                if (missle.IsDestroyed)
                    RemoveMissle(missle);

                var prevPosition = missle.Position;
                missle.UpdatePosition();

                if (!_validater(missle.Position))
                    RemoveMissle(missle);
                else
                    MissleMoved?.Invoke(missle, new MissleMovedHandlerArgs(prevPosition));
            }
        }

        private void RemoveMissle(Missle missle)
        {
            _missles.Remove(missle);
        }

        private void CheckForCollision(WallStore store)
        {
            var map = new Dictionary<Vector2D, Missle>();

            foreach (var missle in _missles.ToList())
            {
                if (RemoveIfDestroyed(missle)) continue;

                var position = missle.Position;
                if (store.ExistsWallAt(position))
                    MisslesCollided?.Invoke(missle, store.GetWallAt(position), new EventArgs());

                if (RemoveIfDestroyed(missle)) continue;

                if (map.ContainsKey(position))
                {
                    var nextMissle = map[position];
                    if (!nextMissle.IsDestroyed)
                        MisslesCollided?.Invoke(missle, nextMissle, new EventArgs());
                }
                else
                    map[position] = missle;
            }
        }

        private bool RemoveIfDestroyed(Missle missle)
        {
            if (missle.IsDestroyed)
            {
                RemoveMissle(missle);
                return true;
            }
            return false;
        }
    }
}
