#define  _CRT_SECURE_NO_WARNINGS

#include "Game.h"
#include "PlayerMovementManager.h"

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
	//wall->showHole(WallHole::HOLE_DIRECTION_X);
	//wall->hideHole();
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
void Game::update()
{
	checkInputKeysAndMovePlayer();
	player->update();
	glm::fvec3 newLightPos = player->getPosition();
	newLightPos.y = 1.5f;
	newLightPos.z += 2.5f;
	light->setPosition(newLightPos);
}

void Game::checkInputKeysAndMovePlayer()
{
	static GameObject * collider;
	GameObject * newCollider = PlayerMovementManager::getLastCollider();
	if (player->isMoving() == false || newCollider != collider)
	{
		if (collider != nullptr)
		{
			collider->setAlpha(1.f);
		}
	}
	MOVEMENT_STATUS status = PlayerMovementManager::checkInputKeysForMovement(player, manager);
	collider = PlayerMovementManager::getLastCollider();

	if (collider != nullptr)
	{
		if (status == MOVE_MOVING_HOLE)
		{
			collider->setAlpha(0.8f);
		}
	}
	if (status == MOVE_NOT_MOVING_COLLISION)
	{
		current_error_text = string("Could not move - collision detected");
	}
	else if (status == MOVE_NOT_ENOUGH_ENERGY)
	{
		current_error_text = string("Not enough energy");
	}
	else if (status != MOVE_NOT_MOVING_NO_COMMANDS)
	{
		current_error_text = string("");
	}
}

void Game::render()
{
	shader->use();
	shader->loadViewMatrix(*(player->getCamera()));
	shader->loadLight(*light);
	shader->unUse();

	renderer->prepare();
	manager->renderAll(renderer, *shader);

	char debugInfo[100];
	settings->font->renderText((GLchar *)current_error_text.c_str(), message_error_pos, glm::fvec3(1.0f, 0.1f, 0.1f), 1.0f);
	sprintf(debugInfo, "X : %3.2f, Y : %3.2f, Z : %3.2f", getPlayer()->getPosition().x, getPlayer()->getPosition().y, getPlayer()->getPosition().z);

	settings->font->renderText(debugInfo, glm::fvec2(0.f, 0.f), glm::fvec3(1.0f, 0.1f, 0.1f), 1.0f);
	//go->render(&renderer, shader);
	Window::update();

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