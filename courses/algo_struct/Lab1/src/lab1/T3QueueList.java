package lab1;

public class T3QueueList {
	public static void main(String[] args) {
		int size = 15;
		T1Queue q = new T1Queue();
		T2UniList list = new T2UniList();
		for (int i = 0; i < size; i++)
			q.enqueue(i % 3);
		System.out.println(q.toString());
		queueToList(q, list);
		System.out.println(list.toString());
	}

	static void queueToList(T1Queue q, T2UniList list) {
		int curI = 0;
		while (!q.isEmpty()) {
			int prevVal = q.dequeue();
			list.insert(curI, prevVal);
			int curCount = 1;
			curI++;
			int size = q.getSize();

			for (int i = 0; i < size; i++) {
				int val = q.dequeue();
				if (val == prevVal) {
					curCount++;
					list.insert(curI, val);
					curI++;
				} else {
					q.enqueue(val);
				}

			}
			list.insert(curI - curCount, curCount);
			curI++;
			reverseQueue(q);
		}
	}

	static void reverseQueue(T1Queue q) {
		int size = q.getSize();
		for (int i = 0; i < size; i++) {
			int val = q.dequeue();
			q.enqueue(val);
		}
	}
}
