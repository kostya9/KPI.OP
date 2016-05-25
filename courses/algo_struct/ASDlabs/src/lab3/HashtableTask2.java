package lab3;

import java.util.LinkedList;
/**
 * This class implements a hash table as an associative array of entries. Hash
 * table does not resolve any collisions
 *
 */
public class HashtableTask2 {

	private LinkedList<Entry>[] table;

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
	@SuppressWarnings("unchecked")
	public HashtableTask2() {
		table = (LinkedList<Entry>[]) new LinkedList[initialCapacity];
		for(int i = 0; i < table.length; i++)
			table[i] = new LinkedList<Entry>();
	}

	/**
	 * Constructs a new, empty hashtable with the specified initial capacity and
	 * default load factor (0.75).
	 * 
	 * @param initialCapacity
	 *            the initial capacity of the hashtable
	 */
	@SuppressWarnings("unchecked")
	public HashtableTask2(int initialCapacity) {
		table = (LinkedList<Entry>[]) new LinkedList[initialCapacity];
		for(int i = 0; i < table.length; i++)
			table[i] = new LinkedList<Entry>();
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
	public HashtableTask2(int initialCapacity, double loadFactor) {
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
	 * Add new entry e - (key, value) to this hashtable.
	 * 
	 * 
	 * @param key
	 *            the hashtable key (choose what is the key in your variant to
	 *            laboratory work)
	 * @param value
	 *            the value (geometric figure according your variant)
	 */
	public GeomFigure put(int key, GeomFigure value) {
		GeomFigure returnValue = this.get(key);
		if(returnValue == null)
		{
			size++;
			if(getLoadFactor() > loadFactor)
				rehash();
		}
		else
		{
			this.remove(key);
		}
		int h = hash(key);
		table[h].add(new Entry(value));
		return returnValue;
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
		
		return getElement(k).getValue();
	
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
		return getElement(key) != null;
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
		Entry e = null;
		int h = hash(key);
		if(getElement(key) != null)
			size--;
		for(int i = 0; i < table[h].size(); i++)
			if(table[h].get(i).getKey() == key)
			{
				e = table[h].remove(i);
				return e.getValue();
			}
		return null;
	
	}

	/**
	 * Increases the capacity of and internally reorganizes this hashtable, in
	 * order to accommodate and access its entries more efficiently. This method
	 * is called automatically when the number of keys in the hashtable exceeds
	 * this hashtable's capacity and load factor
	 */
	@SuppressWarnings("unchecked")
	private void rehash() {
		LinkedList<Entry>[] oldTable = table;
		table = (LinkedList<Entry>[]) new LinkedList[initialCapacity * 2];
		for(int i = 0; i < table.length; i++)
			table[i] = new LinkedList<Entry>();
		
		for(LinkedList<Entry> list : oldTable)
		{
			for(Entry e : list)
				this.put(e.getKey(), e.getValue());
		}

	}
	
	private double getLoadFactor()
	{
		return (double)(size)/table.length;
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
	
	private Entry getElement(int key)
	{
		int h = hash(key);
		for(Entry e : table[h])
			if(e.getKey() == key)
				return e;
		return null;
	}
	public void output()
	{
		for(int i = 0; i < table.length; i++)
		{
			if(table[i].size() == 0)
				System.out.printf("List %d is empty\n", i);
			else
			{
				System.out.printf("List %d : \n", i);
				System.out.printf("\t%-12s%-12s\n", "Key", "Value");
			}
			for(Entry e : table[i])
				System.out.printf("\t%-12s%-12s\n", e.getKey(), e.getValue().toString());
		}
	}

}
