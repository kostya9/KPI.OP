package lab3;

import static org.junit.Assert.*;

import org.junit.Test;

public class MyStringTest {

	@Test
	public void myStringGetLength_CreateHeyy_Length4() {
		MyString str = new MyString("Heyy".toCharArray());
		int expected = 4;
		int actual = str.getLength();
		assertEquals(expected, actual);
	}
	@Test
	public void myStringGetDigitCount_CreateH1eyy32_DIgitCountThree()
	{
		MyString str = new MyString("H1eyy32".toCharArray());
		int expected = 3;
		int actual = str.getDigitCount();
		assertEquals(expected, actual);
	}
	@Test
	public void myStringToString_CreateHeyy_GetHeyy()
	{
		MyString str = new MyString("Heyy".toCharArray());
		String expected = "Heyy";
		String actual = str.toString();
		assertEquals(expected, actual);
	}

}
