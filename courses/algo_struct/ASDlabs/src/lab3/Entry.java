package lab3;

/**
 * Class implements an entry of hash table. Primitive integer value can be used
 * as a key. Object of class GeomFigure is a value.
 *
 */
public class Entry {

	/**
	 * the key is derived value from specified geometric figure
	 */
	private int key;

	/**
	 * specified geometric figure
	 */
	private GeomFigure value;

	public Entry(GeomFigure gf) {

		this.value = gf;
		this.key = gf.getKey();

	}

	public int getKey() {
		return key;
	}

	public GeomFigure getValue() {
		return value;
	}

}
