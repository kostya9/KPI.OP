using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Spells.Domain
{
    public class WallStore
    {
        private readonly Dictionary<Vector2D, WallBlock> _walls;

        internal WallStore()
        {
            this._walls = new Dictionary<Vector2D, WallBlock>();
        }

        public void CreateWall(Vector2D position)
        {
            if(!ExistsWallAt(position))
                _walls[position] = new WallBlock();

            _walls[position].Add(new Wall());
        }

        public IHealthyObject GetHealthyObjectAt(Vector2D position)
        {
            return GetWallAt(position);
        }

        internal Wall GetWallAt(Vector2D position)
        {
            if (!ExistsWallAt(position))
                return null;

            var block = _walls[position];

            return block.GetTop();
        }

        internal bool ExistsWallAt(Vector2D position)
        {
            var contains = _walls.ContainsKey(position);
            if (!contains)
                return false;

            var block = _walls[position];

            if (block.GetTop().HitPoints == 0)
                block.Remove();

            if (block.Count == 0)
                _walls.Remove(position);

            return _walls.ContainsKey(position);
        }
    }
}
