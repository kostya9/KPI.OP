package lab3;

public class Test {

	public static void main(String[] args) {
		System.out.println("Task 1 : \n");
		outputTask1();
		System.out.println("Task 2 : \n");
		outputTask2();
		
	}
	public static void outputTask1()
	{
		Hashtable h = new Hashtable();
		MyString str = new MyString("Heyy".toCharArray());
		MyString str1 = new MyString("Heyy1".toCharArray());
		MyString str2 = new MyString("Heyy12".toCharArray());
		h.put(str.getKey(), str);
		h.put(str1.getKey(), str1);
		h.put(str2.getKey(), str2);
		h.output();
	}
	public static void outputTask2() // two elements with hash 0
	{
		HashtableTask2 h = new HashtableTask2();
		MyString str = new MyString("Heyy".toCharArray());
		MyString str1 = new MyString("Heyy1".toCharArray());
		MyString str2 = new MyString("Heyy12".toCharArray());
		MyString str3 = new MyString("Hey2321321y12".toCharArray());
		MyString str4 = new MyString("Hey121y12".toCharArray());
		h.put(str.getKey(), str);
		h.put(str1.getKey(), str1);
		h.put(str2.getKey(), str2);
		h.put(str3.getKey(), str3);
		h.put(str4.getKey(), str4);
		h.output();
	}

}
