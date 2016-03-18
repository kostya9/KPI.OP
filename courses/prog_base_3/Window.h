#pragma once
#include "MainHeaders.h"
typedef void (*key_callback)(GLFWwindow* window, int key, int scancode, int action, int mode);
class Window
{
	private:
		int width;
		int height;
		GLFWwindow* window;
	public:
		Window(int height = 800, int width = 600);
		void open();
		void close();
		void update();
		void addCallBack(key_callback callback);
};