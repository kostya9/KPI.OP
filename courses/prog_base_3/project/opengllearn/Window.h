#pragma once
#include "MainHeaders.h"
typedef void (*key_callback)(GLFWwindow* window, int key, int scancode, int action, int mode);
class Window
{
	private:
		static int width;
		static int height;
		static GLfloat lastFrameTime;
		static GLfloat deltaTime;
		static GLFWwindow* window;
	public:
		/*Creates a Window default 800x600*/
		/*Opens a window and configures opengl and glfw for it*/
		static void open();
		/*Closes a window and clears glfw configurations*/
		static void close();
		/*Updates the window*/
		static void update();
		static GLfloat getDeltaTime();
		/*Returns glfw pointer to window*/
		static GLFWwindow* getGLFWWindow();
		/*Adds a callback function to key pressing*/
		static void addCallBack(key_callback callback);
		static int getWidth() { return width; }
		static int getHeight() { return height; };
};