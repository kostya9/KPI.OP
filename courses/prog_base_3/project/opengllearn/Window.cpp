#include "Window.h"

int Window::width = 800;
int Window::height = 600;
GLfloat Window::lastFrameTime;
GLfloat Window::deltaTime;
GLFWwindow* Window::window;

void Window::open()
{
	// TODO : WIndow width, height and FOV adjustments
	/*Window::height = height;
	Window::width = width;*/
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(width, height, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();
	// Define the viewport dimensions
	glViewport(0, 0, width, height);
	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST); // Fucking Depth Buffer
	lastFrameTime = glfwGetTime();
}

void Window::close()
{
	glfwTerminate();
}

void Window::update()
{
	glfwSwapBuffers(window);
	GLfloat curFrameTime = glfwGetTime();
	deltaTime = curFrameTime - lastFrameTime;
	lastFrameTime = curFrameTime;
}

GLfloat Window::getDeltaTime()
{
	return deltaTime;
}

GLFWwindow * Window::getGLFWWindow()
{
	return window;
}

void Window::addCallBack(key_callback callback)
{
	glfwSetKeyCallback(window, callback);
}
