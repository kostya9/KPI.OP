package lab3;

import static org.junit.Assert.*;

import org.junit.Test;

import junit.framework.Assert;

public class HashtableTestTask1 {

	@Test
	public void hashtableCreate_Create_SizeZero() {
		Hashtable h = new Hashtable();
		int expected = 0;
		int actual = h.size();
		assertEquals(expected, actual);
	}
	@Test
	public void hashtableSize_CreateAddThreeDeleteOne_SizeTwo()
	{
		Hashtable h = new Hashtable();
		int expected = 2;
		MyString str = new MyString("Heyy".toCharArray());
		MyString str1 = new MyString("Heyy1".toCharArray());
		MyString str2 = new MyString("Heyy12".toCharArray());
		h.put(str.getKey(), str);
		h.put(str1.getKey(), str1);
		h.put(str2.getKey(), str2);
		h.remove(str2.getKey());
		int actual = h.size();
		assertEquals(expected, actual);
		assertEquals(null, h.get(str2.getKey()));
	}
	@Test
	public void hashtableGet_CreateAddThreeGetKeyFive_GetHeyy1()
	{
		Hashtable h = new Hashtable();
		GeomFigure expected = new MyString("Heyy1".toCharArray());
		MyString str = new MyString("Heyy".toCharArray());
		MyString str1 = new MyString("Heyy1".toCharArray());
		MyString str2 = new MyString("Heyy12".toCharArray());
		h.put(str.getKey(), str);
		h.put(str1.getKey(), str1);
		h.put(str2.getKey(), str2);
		GeomFigure actual = h.get(str1.getKey());
		assertEquals(expected.toString(), actual.toString());
	}
	@Test 
	public void hashtableGet_CreateAddThreeGetInappropriateKey_Null()
	{
		Hashtable h = new Hashtable();
		GeomFigure expected = null;
		MyString str = new MyString("Heyy".toCharArray());
		MyString str1 = new MyString("Heyy1".toCharArray());
		MyString str2 = new MyString("Heyy12".toCharArray());
		h.put(str.getKey(), str);
		h.put(str1.getKey(), str1);
		h.put(str2.getKey(), str2);
		GeomFigure actual = h.get(100);
		assertEquals(expected, actual);
	}
	@Test
	public void hashtablePut_PutEqualKeys_False()
	{
		Hashtable h = new Hashtable();
		boolean expected = false;
		MyString str = new MyString("Heyy2".toCharArray());
		MyString str1 = new MyString("Heyy1".toCharArray());
		// SHould return previous value and replace it
		h.put(str.getKey(), str);
		boolean actual = h.put(str1.getKey(), str1);
		assertEquals(expected, actual);
	}

}
