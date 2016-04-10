#pragma once
class Keyboard
{
private:
	bool key_pressed[255];
public:
	Keyboard()
	{
		for (int i = 0; i < 255; i++)
			key_pressed[i] = false;
	}
	void keyPress(char key)
	{
		key_pressed[key] = true;
	}
	void keyRelease(char key)
	{
		key_pressed[key] = false;
	}
	bool isKeyPressed(char key)
	{
		return key_pressed[key];
	}

};