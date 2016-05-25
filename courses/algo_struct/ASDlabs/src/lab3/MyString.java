package lab3;

public class MyString extends GeomFigure {
	char[] symbols;
	MyString(char symbols[])
	{
		this.symbols = symbols;
	}
	@Override
	public int getKey()
	{
		return getLength();
	}
	public int getLength()
	{
		return symbols.length;
	}
	public int getDigitCount()
	{
		int digitCount = 0;
		for(char c : symbols)
			if(Character.isDigit(c))
				digitCount++;
		return digitCount;
	}
	public void output()
	{
		String s = new String(symbols);
		System.out.println(s);
	}
	@Override
	public String toString()
	{
		return String.valueOf(symbols);
	}
}
