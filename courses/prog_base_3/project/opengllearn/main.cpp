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
#include "Wall.h"
#include "WallHole.h"
#include "GameObjectManager.h"

const GLuint WIDTH = 800, HEIGHT = 600;
void window_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
#define arr_size(a) sizeof(a)/sizeof(a[0])
Keyboard * keyboard;

GameObject * loadField(Loader * loader);
void setSineHoleAppearance(Wall * wall);
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
	key_callback kb = window_key_callback;
	Window::addCallBack(kb);
	GameObjectManager * manager = new GameObjectManager();

	Camera camera = Camera();
	Font * font = new Font("fonts/Open_sans/OpenSans-Regular.ttf");

	Field * field = new Field(&loader, 81, glm::vec3(0.0f, 0.0f, 0.0f));
	Player * player = new Player(&loader, glm::vec3(0.0f, 0.5f, 1.0f), camera);
	Wall * wall = new Wall(&loader, glm::vec3(0.0f, 0.01f, 0.0f));
	manager->addObject(field);
	manager->addObject(player);
	manager->addObject(wall);

	glm::vec3 lightPos = glm::vec3(0.0f, 2.0f, 0.0f);
	float light_brightness = .5f;
	Light light = Light(lightPos, glm::vec3(light_brightness, light_brightness, light_brightness));

	char debugInfo[100];
	while (!glfwWindowShouldClose(Window::getGLFWWindow()))
	{
		setSineHoleAppearance(wall);
		sprintf(debugInfo, "X : %3.2f, Y : %3.2f, Z : %3.2f", player->getPosition().x, player->getPosition().y, player->getPosition().z);

		shader.use();
		shader.loadViewMatrix(camera);
		shader.loadLight(light);
		shader.unUse();

		renderer.prepare();
		manager->renderAll(&renderer, shader);
		//go->render(&renderer, shader);
		font->renderText(&renderer, debugInfo, glm::ivec2(12, 43), glm::vec3(0.1f, 0.1f, 0.1f), 1.0f);
		Window::update();
		player->move(manager);
		//camera.move();
	}
	delete manager;
	delete font;
	shader.deleteShader();
	loader.releaseVOs();
	Window::close();
	delete keyboard;
	_getch();
	return 0;
}

void setSineHoleAppearance(Wall * wall)
{
	GLfloat hole = glm::sin(glfwGetTime());
	if (hole > 0.5)
		wall->showHole(WallHole::HOLE_DIRECTION_Z);
	else
		wall->hideHole();
}

GameObject * loadField(Loader * loader)
{
	vector<TexturedModel> models = loader->objToModel("../opengllearn/models/field/field.obj");
	vector<Entity> entities;
	for (TexturedModel model : models)
		entities.push_back(Entity(model));
	return new GameObject(entities, glm::vec3(0.0f, 0.0f, 0.0f));
}
void window_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
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