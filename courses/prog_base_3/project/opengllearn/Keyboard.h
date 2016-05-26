#pragma once
class Keyboard
{
private:
	bool left_button_pressed = false;
	bool key_pressed[1000];
public:
	Keyboard()
	{
		for (int i = 0; i < 1000; i++)
			key_pressed[i] = false;
		left_button_pressed = false;
	}
	void keyPress(int key)
	{
		key_pressed[key] = true;
	}
	void leftButtonPress()
	{
		left_button_pressed = true;
	}
	void leftButtonRelease()
	{
		left_button_pressed = false;
	}
	bool isLeftButtonPressed()
	{
		return left_button_pressed;
	}
	void keyRelease(int key)
	{
		key_pressed[key] = false;
	}
	bool isKeyPressed(int key)
	{
		return key_pressed[key];
	}
	bool isAnythingPressed()
	{
		for (int i = 0; i < 1000; i++)
		{
			if (key_pressed[i] == true)
				return true;
		}
		return false;
	}

};