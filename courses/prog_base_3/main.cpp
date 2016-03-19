#include "MainHeaders.h"

const GLuint WIDTH = 800, HEIGHT = 600;
void key_callback_1(GLFWwindow* window, int key, int scancode, int action, int mode);
#define arr_size(a) sizeof(a)/sizeof(a[0])
Window * curWindow;
// The MAIN function, from here we start the application and run the game loop
int main()
{
	bool close = false;
	Window window = Window(HEIGHT, WIDTH);
	window.open();
	Loader loader = Loader();
	Renderer renderer = Renderer();
	GLfloat vertices[] = {// LEFT TRIANGLE
							-0.5f, 0.5f, 0.0f,
							-0.5f, -0.5f, 0.0f,
							0.5f, -0.5f, 0.0f,
						//RIGHT TRIANGLE
							0.5f, -0.5f, 0.0f,
							0.5f, 0.5f, 0.0f,
							-0.5f, 0.5f, 0.0f}; // QUAD
	Model quad = loader.loadToVao(vertices, arr_size(vertices));
	key_callback kb = key_callback_1;
	window.addCallBack(kb);
	curWindow = &window;
	while (!glfwWindowShouldClose(window.getGLFWWindow()))
	{
		renderer.prepare();
		renderer.render(quad);
		window.update();
	}
	loader.releaseVOs();
	window.close();
	return 0;
}
void key_callback_1(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
		
}