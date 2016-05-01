#define  _CRT_SECURE_NO_WARNINGS

#include "Game.h"
#include "PlayerMovementManager.h"

void window_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
Game::Game()
{
	Window::open();
	manager = new GameObjectManager();
	settings = new Settings();
	settings->font = new Font("fonts/Open_sans/OpenSans-Regular.ttf");
	loader = new GameObjectLoader(manager);
	keyboard = new Keyboard();
	key_callback kb = window_key_callback;
	Window::addCallBack(kb);
}


Keyboard * Game::getKeyboard()
{
	return keyboard;
}

Player * Game::getPlayer()
{
	return manager->getPlayer();
}
void Game::generateField(glm::fvec2 center, GLuint size)
{
	loader->generateField(center, size);
}
void Game::createPlayer(glm::fvec2 position)
{
	loader->createPlayer(position);
}
void Game::createWall(glm::fvec2 position)
{
	loader->createWall(position);
}
void Game::createLight(GLfloat brightness, glm::fvec3 position)
{
	loader->createLight(brightness, position);
}
void Game::update()
{
	Player * player = getPlayer();
	Light * light = manager->getLight();
	checkInputKeysAndMovePlayer();
	player->update();
	glm::fvec3 newLightPos = player->getPosition();
	newLightPos.y = 1.5f;
	newLightPos.z += 2.5f;
	light->setPosition(newLightPos);
}

void Game::render()
{

	manager->renderAll();
	writePlayerPosition();
	Window::update();
	//go->render(&renderer, shader);

}

void Game::checkInputKeysAndMovePlayer()
{
	static GameObject * collider;
	GameObject * newCollider = PlayerMovementManager::getLastCollider();
	removeTransparencyIfAlreadyMoved(newCollider, collider);
	MOVEMENT_STATUS status = PlayerMovementManager::checkInputKeysForMovement(getPlayer(), manager);
	collider = PlayerMovementManager::getLastCollider();
	setTransparencyIfMovingThrough(collider, status);
	updatingErrorMessage(status);
}

void Game::removeTransparencyIfAlreadyMoved(GameObject * newCollider, GameObject * collider)
{
	
	if (getPlayer()->isMoving() == false || newCollider != collider)
	{
		if (collider != nullptr)
		{
			collider->setAlpha(1.f);
		}
	}
}

void Game::updatingErrorMessage(MOVEMENT_STATUS status)
{
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

void Game::setTransparencyIfMovingThrough(GameObject * collider, MOVEMENT_STATUS status)
{
	if (collider != nullptr)
	{
		if (status == MOVE_MOVING_HOLE)
		{
			collider->setAlpha(0.8f);
		}
	}
}
void Game::writePlayerPosition()
{
	char debugInfo[100];
	settings->font->renderText((GLchar *)current_error_text.c_str(), message_error_pos, glm::fvec3(1.0f, 0.1f, 0.1f), 1.0f);
	sprintf(debugInfo, "X : %3.2f, Y : %3.2f, Z : %3.2f", getPlayer()->getPosition().x, getPlayer()->getPosition().y, getPlayer()->getPosition().z);
	settings->font->renderText(debugInfo, glm::fvec2(0.f, 0.f), glm::fvec3(1.0f, 0.1f, 0.1f), 1.0f);
}
Game::~Game()
{
	delete manager;
	delete loader;
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