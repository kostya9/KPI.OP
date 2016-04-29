#include "Game.h"
void window_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
Game::Game()
{
	Window::open();
	settings = new Settings();
	settings->font = new Font("fonts/Open_sans/OpenSans-Regular.ttf");
	shader = new StaticShader();
	renderer = new Renderer(*shader);
	loader = new Loader();
	keyboard = new Keyboard();
	manager = new GameObjectManager();
	key_callback kb = window_key_callback;
	Window::addCallBack(kb);
}

void Game::generateField(glm::fvec2 center, GLuint size)
{
	Field * field = new Field(loader, size, glm::vec3(center.x, 0.0f, center.y));
	manager->addObject(field);
}

void Game::createPlayer(glm::fvec2 position)
{
	Camera * camera = new Camera();
	player = new Player(loader, glm::vec3(0.0f, 0.5f, 1.0f), camera);
	manager->addObject(player);
}

void Game::createWall(glm::fvec2 position)
{
	Wall * wall = new Wall(loader, glm::vec3(position.x, 0.01f, position.y));
	manager->addObject(wall);
}

void Game::createLight(GLfloat brightness, glm::fvec3 position)
{
	light = new Light(position, glm::vec3(brightness, brightness, brightness));
}

Keyboard * Game::getKeyboard()
{
	return keyboard;
}

Player * Game::getPlayer()
{
	return player;
}

void Game::render()
{
	shader->use();
	shader->loadViewMatrix(*(player->getCamera()));
	shader->loadLight(*light);
	shader->unUse();

	renderer->prepare();
	manager->renderAll(renderer, *shader);
	settings->font->renderText((GLchar *)current_error_text.c_str(), message_error_pos, glm::fvec3(1.0f, 0.1f, 0.1f), 1.0f);
	//go->render(&renderer, shader);
	Window::update();
	Player::PLAYER_MOVE_STATUS move_status = player->move(manager);
	if (move_status == Player::COLLISION_DETECTED)
	{
		current_error_text = string("Could not move - collision detected");
	}
	else if (move_status == Player::COLLISION_UNDETECTED)
	{
		current_error_text = string("");
	}
}
Game::~Game()
{
	delete manager;
	delete light;
	shader->deleteShader();
	loader->releaseVOs();
	delete loader;
	delete renderer;
	delete settings;
	Window::close();
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