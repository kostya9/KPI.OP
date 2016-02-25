package lab1;

public class T1Queue {
	/**
	 * Points to the first dequeuing element
	 */
	private int tail;
	/**
	 * Points to next enqueuing element
	 */
	private int head;
	/**
	 * The size of the queue
	 */
	private int size;
	private int[] queueArr;

	public T1Queue() {
		this.size = 0;
		this.queueArr = new int[2];
		this.tail = 0;
		this.head = 0;
	}

	public void enqueue(int el) {
		if (isFull())
			increaseCapacity();
		queueArr[tail] = el;
		shiftTail();
		size++;
	}

	public int dequeue() {
		int val = queueArr[head];
		shiftHead();
		size--;
		return val;
	}

	private void shiftHead() {
		if (isEmpty()) {
			head = 0;
			tail = 0;
			throw new IndexOutOfBoundsException();
		} else
			head = (head + 1) % queueArr.length;
	}

	private void shiftTail() {
		tail = (tail + 1) % queueArr.length;
	}

	private void increaseCapacity() {
		int capacity = queueArr.length;
		int[] queueArr_temp = new int[capacity * 2];
		System.arraycopy(queueArr, head, queueArr_temp, 0, capacity - head);
		System.arraycopy(queueArr, 0, queueArr_temp, capacity - head, tail);
		head = 0;
		tail = capacity;
		queueArr = queueArr_temp;
	}

	public Boolean isFull() {
		return size == queueArr.length;
	}

	public Boolean isEmpty() {
		return size == 0;
	}

	public int getSize() {
		return size;
	}

	public int peek() {
		if (!isEmpty())
			return queueArr[head];
		else
			throw new IndexOutOfBoundsException();
	}

	@Override
	public String toString() {
		String s = "";
		int capacity = queueArr.length;
		s += "[ ";
		for (int i = 0; i < size; i++)
			s += Integer.toString(queueArr[(head + i) % capacity]) + ' ';
		s += "]";
		return s;
	}

}
