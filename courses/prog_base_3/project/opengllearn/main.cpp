#include "MainHeaders.h"
#include "Engine.h"
#include "Keyboard.h"
#include "cstdio"
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

	/*GLfloat vertices[] = {
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
	TexturedModel texturedModel = TexturedModel(quad, texture);*/
	key_callback kb = key_callback_exit;
	window.addCallBack(kb);
	curWindow = &window;
	//vector<TexturedModel> models = loader.objToModel("../opengllearn/models/nanosuit/nanosuit.obj");
	vector<TexturedModel> models = loader.objToModel("../opengllearn/models/stall/stall.obj");
	vector<Entity> entities;
	vector<Entity> lightBulb;
	glm::vec3 lightPos = glm::vec3(5.0f, 3.0f, -8.0f);
		for (TexturedModel model : models)
		{
			entities.push_back(Entity(model, glm::vec3(0.0f, -2.0f, -13.0f), 0.0f, 0.0f, 0.0f, 1.0f));
			lightBulb.push_back(Entity(model, lightPos, 0.0f, 0.0f, 0.0f, 0.05f));
		}
	/*Entity entity = Entity(texturedModel, glm::vec3(0.0f, 0.0f, -5.0f), 0.0f, 0.0f, 0.0f, 1.0f);
	entities.push_back(entity);*/
	int light_brightness = 1;
	Light light = Light(lightPos, glm::vec3(light_brightness, light_brightness, light_brightness));
	entities.insert(entities.end(), lightBulb.begin(), lightBulb.end());
	Camera camera = Camera();

	while (!glfwWindowShouldClose(window.getGLFWWindow()))
	{
		//entity.increasePosition(0.0f, 0.0f, -0.0001f);
		for (Entity & en: entities)
		{
			en.increaseRotation(0.0f, 0.04f, 0.0f);
		}
		//GLfloat curLight = (glm::sin(glfwGetTime()) + 1) * 3;
		//light.setColor(glm::vec3(curLight, curLight, curLight));
		shader.use();
		shader.loadViewMatrix(camera);
		shader.loadLight(light);
		renderer.prepare();
		for (Entity en : entities)
		{
			renderer.render(en, shader);
		}
		shader.unUse();
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
	if (key == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
		return;
	}

	if (key < 255 && isalpha(key))
		key = tolower(key);
	if (action == GLFW_PRESS)
		keyboard->keyPress(key);
	else if (action == GLFW_RELEASE)
		keyboard->keyRelease(key);
}