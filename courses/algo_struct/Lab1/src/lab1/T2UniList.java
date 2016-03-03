package lab1;

public class T2UniList {
	T2UniListNode head; // Signal Node
	int size;

	private class T2UniListNode {
		private T2UniListNode next;
		private int value;

		private T2UniListNode(T2UniListNode next, int value) {
			this.next = next;
			this.value = value;
		}

		private T2UniListNode() {
			this(null, 0);
		}
	}

	public T2UniList() {
		head = new T2UniListNode();
		size = 0;
	}

	private T2UniListNode getNode(int index) {
		T2UniListNode curNode = head;
		for (int i = 0; i < index + 1; i++)
			curNode = curNode.next;
		return curNode;
	}

	public int getValue(int index) {
		if (index >= size || index < 0)
			throw new IndexOutOfBoundsException();

		T2UniListNode curNode = getNode(index);
		return curNode.value;
	}

	public void setValue(int index, int value) {
		if (index >= size || index < 0)
			throw new IndexOutOfBoundsException();

		T2UniListNode curNode = getNode(index);
		curNode.value = value;
	}

	public void insert(int index, int value) {
		if (index > size || index < 0)
			throw new IndexOutOfBoundsException();

		T2UniListNode curNode = getNode(index - 1);
		T2UniListNode newNode = new T2UniListNode(null, value);
		newNode.next = curNode.next;
		curNode.next = newNode;
		size++;
	}

	public int remove(int index) {
		if (index >= size || index < 0)
			throw new IndexOutOfBoundsException();

		T2UniListNode curNode = getNode(index - 1);
		int val = curNode.next.value;
		if (curNode.next != null)
			curNode.next = curNode.next.next;
		size--;
		return val;

	}

	boolean isEmpty() {
		return size == 0;
	}

	public int getSize() {
		return size;
	}

	@Override
	public String toString() {
		String s = "[ ";
		int size = getSize();
		for (int i = 0; i < size; i++) {
			s += Integer.toString(getValue(i)) + " ";
		}
		s += "]";
		return s;
	}

}