#include "MainHeaders.h"
#include "Engine.h"
#include "Keyboard.h"
const GLuint WIDTH = 800, HEIGHT = 600;
void key_callback_exit(GLFWwindow* window, int key, int scancode, int action, int mode);
#define arr_size(a) sizeof(a)/sizeof(a[0])
Window * curWindow;
Keyboard * keyboard;
// The MAIN function, from here we start the application and run the game loop
int main()
{
	bool close = false;
	keyboard = new Keyboard();
	Window window = Window(HEIGHT, WIDTH);
	window.open();
	StaticShader shader = StaticShader();
	Loader loader = Loader();
	Renderer renderer = Renderer(shader);

	GLfloat vertices[] = {
		-0.5f,0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,0.5f,-0.5f,

		-0.5f,0.5f,0.5f,
		-0.5f,-0.5f,0.5f,
		0.5f,-0.5f,0.5f,
		0.5f,0.5f,0.5f,

		0.5f,0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,0.5f,
		0.5f,0.5f,0.5f,

		-0.5f,0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,0.5f,
		-0.5f,0.5f,0.5f,

		-0.5f,0.5f,0.5f,
		-0.5f,0.5f,-0.5f,
		0.5f,0.5f,-0.5f,
		0.5f,0.5f,0.5f,

		-0.5f,-0.5f,0.5f,
		-0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,0.5f

	};

	GLfloat textureCoords[] = {

		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0


	};

	GLuint indices[] = {
		0,1,3,
		3,1,2,
		4,5,7,
		7,5,6,
		8,9,11,
		11,9,10,
		12,13,15,
		15,13,14,
		16,17,19,
		19,17,18,
		20,21,23,
		23,21,22

	};
	Model quad = loader.loadToVao(vertices, arr_size(vertices), indices, arr_size(indices), textureCoords, arr_size(textureCoords));
	Texture texture = Texture(loader.loadTexture("textures/container.jpg"));
	TexturedModel texturedModel = TexturedModel(quad, texture);
	key_callback kb = key_callback_exit;
	window.addCallBack(kb);
	curWindow = &window;

	Entity entity = Entity(texturedModel, glm::vec3(0.0f, 0.0f, -5.0f), 0.0f, 0.0f, 0.0f, 1.0f);
	Camera camera = Camera();

	while (!glfwWindowShouldClose(window.getGLFWWindow()))
	{
		//entity.increasePosition(0.0f, 0.0f, -0.0001f);
		entity.increaseRotation(-0.04f, -0.04f, 0);
		shader.use();
		shader.loadViewMatrix(camera);
		shader.unUse();
		renderer.prepare();
		renderer.render(entity, shader);
		window.update();
		camera.move();
	}
	shader.deleteShader();
	loader.releaseVOs();
	window.close();
	delete keyboard;
	return 0;
}
void key_callback_exit(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_W)
	{
		if (action == GLFW_PRESS)
			keyboard->keyPress('w');
		else if (action == GLFW_RELEASE)
			keyboard->keyRelease('w');
	}
	else if (key == GLFW_KEY_S)
	{
		if (action == GLFW_PRESS)
			keyboard->keyPress('s');
		else if (action == GLFW_RELEASE)
			keyboard->keyRelease('s');
	}
	else if (key == GLFW_KEY_D)
	{
		if (action == GLFW_PRESS)
			keyboard->keyPress('d');
		else if (action == GLFW_RELEASE)
			keyboard->keyRelease('d');
	}
	else if (key == GLFW_KEY_A)
	{
		if (action == GLFW_PRESS)
			keyboard->keyPress('a');
		else if (action == GLFW_RELEASE)
			keyboard->keyRelease('a');
	}
	else if (key == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}