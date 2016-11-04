using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Spells.Domain
{
    public class WallStore
    {
        private readonly Dictionary<Vector2D, Wall> _walls;

        public WallStore()
        {
            this._walls = new Dictionary<Vector2D, Wall>();
        }

        public void CreateWall(Vector2D position)
        {
            if(ExistsWallAt(position))
                throw new PositionIsOccupiedException(position);

            _walls[position] = new Wall();
        }

        public Wall GetWallAt(Vector2D position)
        {
            if(!ExistsWallAt(position))
                return null;

            return _walls[position];
        }

        public bool ExistsWallAt(Vector2D position)
        {
            return _walls.ContainsKey(position);
        }
    }
}
