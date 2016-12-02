using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;
using System.Xml.Serialization;

namespace Spells.Domain
{
    [Serializable]
    [DataContract]
    public class WallBlock : ICollection<Wall>, IEnumerable<Wall>, IEnumerator<Wall>, ICollidable
    {
        [DataMember]
        [XmlArray("Walls")]
        [XmlArrayItem("Wall")]
        public List<Wall> Walls { get; private set; }
        private IEnumerator<Wall> EnumeratorImplementation => Walls.GetEnumerator();

        public WallBlock()
        {
            Walls = new List<Wall>();
        }

        public IEnumerator<Wall> GetEnumerator()
        {
            return Walls.GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        public void Add(Wall item)
        {
            Walls.Add(item);
            Walls.Sort();
        }

        public void Clear()
        {
            Walls = new List<Wall>();
        }

        public bool Contains(Wall item)
        {
            return Walls.Contains(item);
        }

        public void CopyTo(Wall[] array,
            int arrayIndex)
        {
            Array.Copy(Walls.ToArray(), array, arrayIndex);
        }

        public bool Remove(Wall item)
        {
            throw new NotImplementedException();
        }

        internal void ChangeHitpoints(Func<Wall, int> changer, Action<Wall> error)
        {
            Walls.ForEach(w =>
            {
                try
                {
                    w.HitPoints = changer(w);
                }
                catch (ArgumentException)
                {
                    error(w);
                }
            });
        }


        public Wall Remove()
        {
            var wall = GetTop();
            Walls.RemoveAt(0);
            return wall;
        }

        public Wall GetTop()
        {
            return Walls.ElementAt(0);
        }

        public int Count => Walls.Count;
        public bool IsReadOnly => false;
        public void Dispose()
        {
            EnumeratorImplementation.Dispose();
        }

        public bool MoveNext()
        {
            return EnumeratorImplementation.MoveNext();
        }

        public void Reset()
        {
            EnumeratorImplementation.Reset();
        }

        public Wall Current => EnumeratorImplementation.Current;

        object IEnumerator.Current => ((IEnumerator) EnumeratorImplementation).Current;
        public bool IsDestroyed => GetTop() == null || GetTop().IsDestroyed;
        public void Collide(ICollidable other)
        {
            GetTop()?.Collide(other);
            
        }
    }
}
