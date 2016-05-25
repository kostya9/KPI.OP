package lab3;

/**
 * This class implements a hash table as an associative array of entries. Hash
 * table does not resolve any collisions
 *
 */
public class Hashtable {

	private Entry[] table;

	/**
	 * the number of non-null entries in the hashtable
	 */
	private int size;

	/**
	 * default size of the hashtable
	 */
	private final int initialCapacity = 11;

	/**
	 * The load factor is a measure of how full the hash table is allowed to get
	 * / before its capacity is automatically increased
	 */
	private double loadFactor = 0.75;

	/**
	 * A is used in multiplication hash function
	 */
	private final double A = (Math.sqrt(5) - 1)/2;

	/**
	 * Constructs a new, empty hashtable with a default initial capacity (11)
	 * and load factor (0.75).
	 */
	public Hashtable() {
		table = new Entry[initialCapacity];
	}

	/**
	 * Constructs a new, empty hashtable with the specified initial capacity and
	 * default load factor (0.75).
	 * 
	 * @param initialCapacity
	 *            the initial capacity of the hashtable
	 */
	public Hashtable(int initialCapacity) {
		table = new Entry[initialCapacity];
	}

	/**
	 * Constructs a new, empty hashtable with the specified initial capacity and
	 * the specified load factor.
	 * 
	 * @param initialCapacity
	 *            the initial capacity of the hashtable
	 * @param loadFactor
	 *            the load factor of the hashtable
	 */
	public Hashtable(int initialCapacity, double loadFactor) {
		this(initialCapacity);
		this.loadFactor = loadFactor;

	}

	/**
	 * Tests if the hashtable contains no entries.
	 * 
	 * @return true if the hashtable contains no entries; false otherwise
	 */
	public boolean isEmpty() {
		return size == 0;
	}

	/**
	 * Returns the number of entries in the hashtable
	 * 
	 * @return the number of entries in the hashtable
	 */
	public int size() {
		return size;
	}

	/**
	 * Tests if some key maps to the specified value in this hashtable
	 * 
	 * @param key
	 *            possible key (non-null value)
	 * @return true if and only if some key maps to the value argument in this
	 *         hashtable; false otherwise
	 */
	public boolean contains(int key) {

		int h = hash(key);
		return table[h] != null;
	}

	/**
	 * If hashtable contains an entry e = (k, v), with key equals to k, then
	 * return the value v, for e; else return null
	 * 
	 * @param k
	 *            the key whose associated value is to be returned
	 * @return the value to which the specified key is mapped, or null if this
	 *         hashtable contains no mapping for the key
	 */
	public GeomFigure get(int k) {
		if(!contains(k))
			return null;
		
		int h = hash(k);
		return table[h].getValue();

	}

	/**
	 * Increases the capacity of and internally reorganizes this hashtable, in
	 * order to accommodate and access its entries more efficiently. This method
	 * is called automatically when the number of keys in the hashtable exceeds
	 * this hashtable's capacity and load factor
	 */
	private void rehash() {
		Entry[] oldTable = table;
		table = new Entry[table.length * 2];
		for(Entry e : oldTable)
		{
			this.put(e.getKey(), e.getValue());
		}

	}
	
	private double getLoadFactor()
	{
		return (double)(size)/table.length;
	}

	/**
	 * Add new entry e - (key, value) to this hashtable.
	 * 
	 * if table does not have an entry with key , than add entry e = (key,
	 * value) to table and return null;
	 * 
	 * else, replace with value the existing value of the entry with key and
	 * return old value
	 * 
	 * @param key
	 *            the hashtable key (choose what is the key in your variant to
	 *            laboratory work)
	 * @param value
	 *            the value (geometric figure according your variant)
	 * @return null if new entry was added; else old value that was replaced
	 */
	public boolean put(int key, GeomFigure value) {
		int h = hash(key);
		if(table[h] == null)
		{
			size++;
			table[h] = new Entry(value);
			if(getLoadFactor() > loadFactor)
				rehash();
			return true;
		}
		else
			return false;

	}

	/**
	 * The hash function is used to map the search key to an index of this
	 * hashtable. Choose hashing method from your variant to laboratory work
	 * 
	 * @param key
	 *            key - some integer value
	 * @return hash value - index in table
	 */
	private int hash(int key) {
		double fracPart = key * A - (int)(key * A);
		return (int)(table.length * fracPart);
	}

	/**
	 * Removes the key (and its corresponding value) from this hashtable. This
	 * method does nothing if the key is not in the hashtable
	 * 
	 * 
	 * @param key
	 *            the key that needs to be removed
	 * @return the value to which the key had been mapped in this hashtable, or
	 *         null if the key did not have a mapping
	 */
	public GeomFigure remove(int key) {
		int h = hash(key);
		if(table[h] != null)
			size--;
		GeomFigure fig = table[h].getValue();
		table[h] = null;
		return fig;

	}
	public void output()
	{
		System.out.printf("\t%-12s%-12s\n", "Key", "Value");
		for(int i = 0; i < this.table.length; i++)
		{
			if(table[i] != null)
			{
				System.out.printf("Entry %d : \n", i);
				System.out.printf("\t%-12s%-12s\n", table[i].getKey(), table[i].getValue().toString());
			}
			else
			{
				System.out.printf("Entry %d is empty \n", i);
			}
			
		}
	}

}
