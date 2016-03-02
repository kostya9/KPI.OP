package lab1;

import static org.junit.Assert.*;

import org.junit.Test;

public class T2UniListTest {

	public static void main(String[] args) {
		T2UniList l = new T2UniList();
		
	}
	
	@Test(expected=IndexOutOfBoundsException.class)
	public void testInsertIntoNonExistantIndex()
	{
		T2UniList list = new T2UniList();
		list.insert(1, 1);
	}
	
	@Test(expected=IndexOutOfBoundsException.class)
	public void testGetFromNonExistantIndex()
	{
		T2UniList list = new T2UniList();
		list.getValue(0);
	}
	
	@Test(expected=IndexOutOfBoundsException.class)
	public void testDeleteFromEmptyList()
	{
		T2UniList list = new T2UniList();
		list.remove(0);
	}
	
	@Test
	public void testAddFirstGetIt()
	{
		T2UniList list = new T2UniList();
		list.insert(0, 1);
		list.insert(0, 2);
		int actual = list.getValue(0);
		int expected = 2;
		System.out.println("Inserted values 1 and 2 into the last position");
		System.out.println(list.toString());
		assertEquals(expected, actual);
		actual = list.getValue(1);
		expected = 1;
		assertEquals(expected, actual);
		System.out.println("Success\n");
	}
	
	@Test
	public void testAddLastGetIt()
	{
		T2UniList list = new T2UniList();
		list.insert(list.getSize(), 1);
		list.insert(list.getSize(), 2);
		System.out.println("Inserted values 1 and 2 into the first position");
		System.out.println(list.toString());
		int actual = list.getValue(1);
		int expected = 2;
		assertEquals(expected, actual);
		actual = list.getValue(0);
		expected = 1;
		assertEquals(expected, actual);
		System.out.println("Success\n");
	}
	
	@Test
	public void testRemove()
	{
		T2UniList list = new T2UniList();
		list.insert(list.getSize(), 1);
		list.insert(list.getSize(), 2);
		list.insert(list.getSize(), 3);
		list.remove(0);
		System.out.println("Added values 1, 2 and 3 to the list. Deleted the first value");
		System.out.println(list.toString());
		int actual = list.getValue(0);
		int expected = 2;
		assertEquals(expected, actual);
		list.remove(list.getSize() - 1);
		System.out.println("Deleted the last value");
		System.out.println(list.toString());
		actual = list.getValue(list.getSize() - 1);
		expected = 2;
		assertEquals(expected, actual);
		System.out.println("Success\n");
	}
	/*static void printAddValue(T2UniList l, int value)
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
	}*/

}
