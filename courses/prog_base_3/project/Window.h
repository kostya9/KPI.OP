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
		/*Creates a Window default 800x600*/
		Window(int width = 800, int height= 600);
		/*Opens a window and configures opengl and glfw for it*/
		void open();
		/*Closes a window and clears glfw configurations*/
		void close();
		/*Updates the window*/
		void update();
		/*Returns glfw pointer to window*/
		GLFWwindow* getGLFWWindow();
		/*Adds a callback function to key pressing*/
		void addCallBack(key_callback callback);
};