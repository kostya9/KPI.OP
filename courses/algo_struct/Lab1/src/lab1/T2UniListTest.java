package lab1;

public class T2UniListTest {

	public static void main(String[] args) {
		T2UniList l = new T2UniList();
		printDeleteValue(l, 0);
		printAddValue(l, 6);
		printAddValue(l, 4);
		printAddValue(l, 100);
		printAddValue(l, 99);
		printAddValue(l, 65);
		printGetValue(l, 3);
		printGetValue(l, 100);
		printAddValue(l, 100, 1000);
		printDeleteValue(l, 0);
		printDeleteValue(l, 2);
		System.out.println(l.getSize());
		
	}
	static void printAddValue(T2UniList l, int value)
	{
		String s = "";
		try
		{
			l.addValue(value);
			s = "Adding value " + Integer.toString(value) + " to the end of the list";
		}
		catch(Exception e)
		{
			s = "Caught Exception : \n" + e.getClass();
		}
		finally
		{
			System.out.println(s);
			System.out.println(l.toString());
		}
	}
	static void printAddValue(T2UniList l, int value, int index)
	{
		String s = "";
		try
		{
			l.addValue(index, value);
			s = "Adding value " + Integer.toString(value);
			
		}
		catch(Exception e)
		{
			s = "Caught Exception : \n" + e.getClass();
		}		
		finally
		{
			System.out.println(s);
			System.out.println(l.toString());
		}
		
	}
	static void printDeleteValue(T2UniList l, int index)
	{
		String s = "";
		try
		{
			int value = l.deleteValue(index);
			s = "Deleting value " + Integer.toString(value);
		}
		catch(Exception e)
		{
			s = "Caught Exception : \n" + e.getClass();
		}
		finally
		{
			System.out.println(s);
			System.out.println(l.toString());
		}
	}
	static void printGetValue(T2UniList l, int index)
	{
		String s = "";
		try
		{
			int value = l.getValue(index);
			s = "Got the value " + Integer.toString(value) + " at index " + Integer.toString(index);
		}
		catch(Exception e)
		{
			s = "Caught Exception : \n" + e.getClass();
		}
		finally
		{
			System.out.println(s);
			System.out.println(l.toString());
		}
	}

}
