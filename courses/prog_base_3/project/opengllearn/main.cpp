#include "MainHeaders.h"
#include "Engine.h"
const GLuint WIDTH = 800, HEIGHT = 600;
void key_callback_exit(GLFWwindow* window, int key, int scancode, int action, int mode);
#define arr_size(a) sizeof(a)/sizeof(a[0])
Window * curWindow;
// The MAIN function, from here we start the application and run the game loop
int main()
{
	bool close = false;
	Window window = Window(HEIGHT, WIDTH);
	window.open();
	StaticShader shader = StaticShader();
	Loader loader = Loader();
	Renderer renderer = Renderer();
	GLfloat vertices[] = {	-0.5f, 0.5f, 0.0f,	// Vertex 0
							-0.5f, -0.5f, 0.0f,	// Vertex 1
							0.5f, -0.5f, 0.0f,	// Vertex 2
							0.5f, 0.5f, 0.0f}; // Vertex 3

	GLuint indices[] = {0, 1, 3,	// Left Triangle
						3, 1, 2		// Right Triangle
	};
	Model quad = loader.loadToVao(vertices, arr_size(vertices), indices, arr_size(indices));
	key_callback kb = key_callback_exit;
	window.addCallBack(kb);
	curWindow = &window;
	while (!glfwWindowShouldClose(window.getGLFWWindow()))
	{
		renderer.prepare();
		shader.use();
		renderer.render(quad);
		shader.unUse();
		window.update();
	}
	shader.deleteShader();
	loader.releaseVOs();
	window.close();
	return 0;
}
void key_callback_exit(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
		
}