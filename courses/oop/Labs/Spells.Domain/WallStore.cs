using System;
using System.CodeDom;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.Xml.Serialization;

namespace Spells.Domain
{
    public class WallStore : IDisposable
    {
        private bool disposed = false;
        private readonly Dictionary<Vector2D, WallBlock> _walls;
        private readonly string _serializationType = "json";
        internal WallStore()
        {
            this._walls = new Dictionary<Vector2D, WallBlock>();
        }

        public void SerializeFirst()
        {
            var block = _walls.FirstOrDefault().Value;
            switch (_serializationType)
            {
                case "xml":
                {
                    
                    XmlSerializer serializer = new XmlSerializer(typeof(WallBlock), new Type[] { typeof(Wall) });
                    using (var file = File.Create("text.xml"))
                    {
                        serializer.Serialize(file, block);
                    }
                }
                    break;
                case "json":
                {
                        DataContractJsonSerializer serializer = new DataContractJsonSerializer(typeof(WallBlock), new [] {typeof(Wall)});
                        using (var file = File.Create("text.json"))
                        {
                            serializer.WriteObject(file, block);
                        }
                    }
                    break;
            }

        }

        public void DeserializeFirst()
        {
            var pos = new Vector2D(0, 0);
            var block = _walls[pos];
            _walls.Remove(pos);
            switch (_serializationType)
            {
                case "xml":
                {
                    XmlSerializer serializer = new XmlSerializer(typeof(WallBlock), new Type[] { typeof(Wall) });
                    using (var file = File.OpenRead("text.xml"))
                    {
                        block = (WallBlock)serializer.Deserialize(file);
                    }
                }
                break;
                case "json":
                {
                    DataContractJsonSerializer serializer = new DataContractJsonSerializer(typeof(WallBlock), new[] { typeof(Wall) });
                    using (var file = File.OpenRead("text.json"))
                    {
                            block = (WallBlock)serializer.ReadObject(file);
                    }
                }
                break;
            }
            _walls[pos] = block;

        }

        internal void AddWallBlock(Vector2D position, WallBlock block)
        {
            if (!ExistsWallAt(position))
                this._walls[position] = block;
        }

        public void CreateWall(Vector2D position)
        {
            if (!ExistsWallAt(position))
                _walls[position] = new WallBlock();

            _walls[position].Add(new Wall());
        }

        public IHealthyObject GetHealthyObjectAt(Vector2D position)
        {
            return GetWallAt(position).GetTop();
        }

        internal WallBlock GetWallAt(Vector2D position)
        {
            if (!ExistsWallAt(position))
                return null;

            var block = _walls[position];

            return block;
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

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (disposed)
                return;

            if (disposing)
            {
                foreach (var wallKeyValuePair in _walls)
                {
                    wallKeyValuePair.Value.Dispose();
                }
            }
            disposed = true;
        }

        ~WallStore()
        {
            Dispose(false);
        }
    }
}
