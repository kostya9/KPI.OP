#pragma once
class Keyboard
{
private:
	bool key_pressed[1000];
public:
	Keyboard()
	{
		for (int i = 0; i < 1000; i++)
			key_pressed[i] = false;
	}
	void keyPress(int key)
	{
		key_pressed[key] = true;
	}
	void keyRelease(int key)
	{
		key_pressed[key] = false;
	}
	bool isKeyPressed(int key)
	{
		return key_pressed[key];
	}

};