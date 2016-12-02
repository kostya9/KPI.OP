using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Spells.Domain
{
    class WallBlock : ICollection<Wall>, IEnumerable<Wall>, IEnumerator<Wall>
    {
        private List<Wall> _walls;
        private IEnumerator<Wall> EnumeratorImplementation => _walls.GetEnumerator();

        public WallBlock()
        {
            _walls = new List<Wall>();
        }

        public IEnumerator<Wall> GetEnumerator()
        {
            return _walls.GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        public void Add(Wall item)
        {
            _walls.Add(item);
            _walls.Sort();
        }

        public void Clear()
        {
            _walls = new List<Wall>();
        }

        public bool Contains(Wall item)
        {
            return _walls.Contains(item);
        }

        public void CopyTo(Wall[] array,
            int arrayIndex)
        {
            Array.Copy(_walls.ToArray(), array, arrayIndex);
        }

        public bool Remove(Wall item)
        {
            throw new NotImplementedException();
        }


        public Wall Remove()
        {
            var wall = GetTop();
            _walls.RemoveAt(0);
            return wall;
        }

        public Wall GetTop()
        {
            return _walls.ElementAt(0);
        }

        public int Count => _walls.Count;
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
    }
}
