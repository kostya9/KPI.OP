package lab3;

import static org.junit.Assert.*;

import org.junit.Test;

public class HashTableTestTask2And3 {

	@Test
	public void hashtableCreate_Create_SizeZero() {
		HashtableTask2 h = new HashtableTask2();
		int expected = 0;
		int actual = h.size();
		assertEquals(expected, actual);
	}
	@Test
	public void hashtableSize_CreateAddThreeDeleteOne_SizeTwo()
	{
		HashtableTask2 h = new HashtableTask2();
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
	}
	@Test
	public void hashtableGet_CreateAddThreeGetKeyFive_GetHeyy1()
	{
		HashtableTask2 h = new HashtableTask2();
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
	public void hashtableGet_CreateAddTenGetKey20_GetHeywsasads2321321y12() // 2 Entries At 7th list key 7 and 20
	{
		HashtableTask2 h = new HashtableTask2();
		MyString str = new MyString("Hewwwwy".toCharArray());
		MyString str1 = new MyString("Heyy1".toCharArray());
		MyString str2 = new MyString("Heqqqqyy12".toCharArray());
		MyString str3 = new MyString("Hey2321321y12".toCharArray());
		MyString str4 = new MyString("Hey121y12".toCharArray());
		MyString str5 = new MyString("He2321yy".toCharArray());
		MyString str6 = new MyString("Heyyasddasdasdasdaddsasdas1".toCharArray());
		MyString str7 = new MyString("Heydfs1afasy12".toCharArray());
		MyString str8 = new MyString("Heywsasads2321321y12".toCharArray());
		MyString str9 = new MyString("Hey1xzxxcdxxzc21y12".toCharArray());
		h.put(str.getKey(), str);
		h.put(str1.getKey(), str1);
		h.put(str2.getKey(), str2);
		h.put(str3.getKey(), str3);
		h.put(str4.getKey(), str4);
		h.put(str5.getKey(), str5);
		h.put(str6.getKey(), str6);
		h.put(str7.getKey(), str7);
		h.put(str8.getKey(), str8);
		h.put(str9.getKey(), str9);
		GeomFigure expected = str8;
		GeomFigure actual = h.get(20);
		assertEquals(expected.toString(), actual.toString());
		//assertEquals(expected.toString(), actual.toString());
	}
	@Test
	public void hashtableRemove_CreateAddTenRemove20Get20_GetNull()
	{
		HashtableTask2 h = new HashtableTask2();
		MyString str = new MyString("Hewwwwy".toCharArray());
		MyString str1 = new MyString("Heyy1".toCharArray());
		MyString str2 = new MyString("Heqqqqyy12".toCharArray());
		MyString str3 = new MyString("Hey2321321y12".toCharArray());
		MyString str4 = new MyString("Hey121y12".toCharArray());
		MyString str5 = new MyString("He2321yy".toCharArray());
		MyString str6 = new MyString("Heyyasddasdasdasdaddsasdas1".toCharArray());
		MyString str7 = new MyString("Heydfs1afasy12".toCharArray());
		MyString str8 = new MyString("Heywsasads2321321y12".toCharArray());
		MyString str9 = new MyString("Hey1xzxxcdxxzc21y12".toCharArray());
		h.put(str.getKey(), str);
		h.put(str1.getKey(), str1);
		h.put(str2.getKey(), str2);
		h.put(str3.getKey(), str3);
		h.put(str4.getKey(), str4);
		h.put(str5.getKey(), str5);
		h.put(str6.getKey(), str6);
		h.put(str7.getKey(), str7);
		h.put(str8.getKey(), str8);
		h.put(str9.getKey(), str9);
		h.remove(20);
		GeomFigure expected = null;
		GeomFigure actual = h.get(20);
		assertEquals(expected, actual);
	}
	@Test
	public void hashtablePut_PutEqualKeys_ReplaceAndGetPrevious()
	{
		HashtableTask2 h = new HashtableTask2();
		GeomFigure expected = new MyString("Heyy2".toCharArray());
		MyString str = new MyString("Heyy2".toCharArray());
		MyString str1 = new MyString("Heyy1".toCharArray());
		// Should return previous value and replace it
		h.put(str.getKey(), str);
		GeomFigure actual = h.put(str1.getKey(), str1);
		assertEquals(expected.toString(), actual.toString());
		// Get the current value with the key
		expected = str1;
		actual = h.get(str.getKey());
		assertEquals(expected.toString(), actual.toString());
	}
	@Test 
	public void hashtableGet_CreateAddThreeGetInappropriateKey_Null()
	{
		HashtableTask2 h = new HashtableTask2();
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

}
