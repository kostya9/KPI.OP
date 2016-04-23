#define _CRT_SECURE_NO_WARNINGS
#include "MainHeaders.h"
#include "Engine.h"
#include "Keyboard.h"
#include "GameObject.h"
#include "cstdio"
#include "Player.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Field.h"
#include "Font.h"


const GLuint WIDTH = 800, HEIGHT = 600;
void key_callback_exit(GLFWwindow* window, int key, int scancode, int action, int mode);
#define arr_size(a) sizeof(a)/sizeof(a[0])
Keyboard * keyboard;
GameObject * loadField(Loader * loader);
// The MAIN function, from here we start the application and run the game loop
int main()
{
	// INIT
	bool close = false;
	keyboard = new Keyboard();
	Window::open();
	StaticShader shader = StaticShader();
	Loader loader = Loader();
	Renderer renderer = Renderer(shader);
	key_callback kb = key_callback_exit;
	Window::addCallBack(kb);


	vector<TexturedModel> models = loader.objToModel("../opengllearn/models/nanosuit/nanosuit.obj");
	//vector<TexturedModel> models = loader.objToModel("../opengllearn/models/stall/stall.obj");
	vector<Entity> entities;
	for (TexturedModel model : models)
			entities.push_back(Entity(model));
	GameObject * go = new GameObject(entities, glm::vec3(0.0f,0.0f,-20.0f));
	glm::vec3 lightPos = glm::vec3(0.0f, 2.0f, 0.0f);
	Camera camera = Camera();
	camera.moveUp(3.0f);
	camera.pitch(M_PI / 2.0f);
	//Player * player = new Player(player_e, glm::vec3(0.0f, 0.0f, -3.0f), camera);
		/*Entity entity = Entity(texturedModel, glm::vec3(0.0f, 0.0f, -5.0f), 0.0f, 0.0f, 0.0f, 1.0f);
	entities.push_back(entity);*/
	Field * field = new Field(&loader, 81, glm::vec3(0.0f, 0.0f, 0.0f));
	Font * font = new Font("fonts/Open_sans/OpenSans-Regular.ttf");
	
	//field->rotate(glm::vec3(0.0f, 90.0f, 0.0f));
	float light_brightness = 0.7f;
	Light light = Light(lightPos, glm::vec3(light_brightness, light_brightness, light_brightness));
	float timePrev = glfwGetTime();
	//field->scale(3);
	char debugInfo[100];
	//go->hideObject();
	while (!glfwWindowShouldClose(Window::getGLFWWindow()))
	{
		//entity.increasePosition(0.0f, 0.0f, -0.0001f);
		//GLfloat curLight = (glm::sin(glfwGetTime()) + 1) * 3;
		//light.setColor(glm::vec3(curLight, curLight, curLight));
		sprintf(debugInfo, "X : %3.2f, Y : %3.2f, Z : %3.2f", camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
		shader.use();
		shader.loadViewMatrix(camera);
		shader.loadLight(light);
		renderer.prepare();
		field->render(&renderer, shader);
		go->render(&renderer, shader);
		font->renderText(&renderer, debugInfo, glm::ivec2(12, 43), glm::vec3(0.1f, 0.1f, 0.1f), 1.0f);
		shader.unUse();
		Window::update();
		camera.move();
	}
	shader.deleteShader();
	loader.releaseVOs();
	Window::close();
	delete keyboard;
	return 0;
}

GameObject * loadField(Loader * loader)
{
	vector<TexturedModel> models = loader->objToModel("../opengllearn/models/field/field.obj");
	vector<Entity> entities;
	for (TexturedModel model : models)
		entities.push_back(Entity(model));
	return new GameObject(entities, glm::vec3(0.0f, 0.0f, 0.0f));
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