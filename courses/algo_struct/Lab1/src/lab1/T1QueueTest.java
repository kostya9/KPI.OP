package lab1;

import java.util.Random;

public class T1QueueTest {

	public static void main(String[] args) {
		int test_count = 100;
		Random random = new Random();
		T1Queue q = new T1Queue();
		for (int i = 0; i < test_count; i++) {
			if (random.nextInt() % 2 == 0)
				printEnqueue(q, i);
			else
				printDequeue(q);
		}

	}

	static void printDequeue(T1Queue q) {
		int val;
		String output = "";
		try {
			val = q.dequeue();
			output = "The dequeued element is " + val + "\n" + q.toString();
		} catch (IndexOutOfBoundsException e) {
			output = "The queue is empty";
		} finally {
			System.out.println(output);
		}
	}

	static void printEnqueue(T1Queue q, int el) {
		String output = "";
		q.enqueue(el);
		output = "The enqueued element is " + el + "\n" + q.toString();
		System.out.println(output);
	}
}
