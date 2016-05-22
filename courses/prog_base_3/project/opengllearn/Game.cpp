#define  _CRT_SECURE_NO_WARNINGS

#include "Game.h"
#include "PlayerMovementManager.h"
#include "NewGameMenuOption.h"
#include "ExitMenuOption.h"
void window_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
Game::Game()
{
	Window::open();
	manager = new GameObjectManager();
	settings = new Settings();
	settings->font = new Font("fonts/Open_sans/OpenSans-Regular.ttf");
	loader = new GameObjectLoader(manager);
	keyboard = new Keyboard();
	Light * light = new Light(glm::fvec3(0.0f, 0.0f, 0.0f), glm::fvec3(1.0f, 1.0f, 1.0f));
	manager->addObject(light);
	key_callback kb = window_key_callback;
	Window::addCallBack(kb);
	setState(GAME_MENU);

	this->menu = new Menu(this);
	manager->addObject(menu);

	//MenuOptionButton * button = new MenuOptionButton(&Loader(), settings->font, glm::fvec3(1.0f, 1.0f, 1.0f), string("HEYYY"));
	//MenuOptionButton * button1 = new MenuOptionButton(&Loader(), settings->font, glm::fvec3(1.0f, 1.0f, 1.0f), string("HEYYY1"));
	NewGameMenuOption * newGame = new NewGameMenuOption(&Loader(), settings->font, glm::fvec3(1.0f, 1.0f, 1.0f));
	ExitMenuOption * buttonExit = new ExitMenuOption(&Loader(), settings->font, glm::fvec3(1.0f, 1.0f, 1.0f));
	menu->addMenuOption(newGame);
	//menu->addMenuOption(button);
	//menu->addMenuOption(button1);
	menu->addMenuOption(buttonExit);
}


Keyboard * Game::getKeyboard()
{
	return keyboard;
}

Player * Game::getPlayer()
{
	return manager->getPlayer();
}
Field * Game::getField()
{
	return manager->getField();
}
void Game::setState(GameState state)
{
	
	cleanGameObjects();
	this->state = state;
	if (state == GAME_MENU)
	{
		this->manager->addObject(menu);
		loader->generateField(glm::fvec2(0.0f, 0.0f), 7);
		loader->createPlayer(glm::fvec2(2.0f, -2.0f));
		loader->createWall(glm::fvec2(-2.0f, 0.f));
		loader->createWall(glm::fvec2(2.0f, 0.f));
		loader->createShadow(getPlayer()->getPosition());
	}
}
void Game::cleanGameObjects()
{
	delete this->manager;
	delete this->loader;
	current_error_text = string();
	current_info_text = string();
	lastCollider = nullptr;
	manager = new GameObjectManager();
	loader = new GameObjectLoader(manager);
	Light * light = new Light(glm::fvec3(0.0f, 0.0f, 0.0f), glm::fvec3(1.0f, 1.0f, 1.0f));
	manager->addObject(light);
}
void Game::loadLevel(string path)
{
	loader->loadLevel(path);
	loader->createShadow(getPlayer()->getPosition());
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
void Game::createWhiteHole(glm::fvec2 position)
{
	this->loader->creatWhiteHole(position);
}
void Game::update()
{
	if (state == GAME_ACTIVE)
	{
		// endGameIfOutOfField(); // SHould I?
		if (winIfAtWhiteHole() == false)
		{
			checkInputKeysAndMovePlayer();
			if (isEnoughEnergy() == false)
			{
				manager->addMask(glm::fvec3(0.7f, 0.5f, 0.5f));
				lose();
				return;
			}
			if (manager->getShadow()->isAtPositionNeighborhood(getPlayer()->getPosition()))
				getPlayer()->startDamaging(100);
			getPlayer()->update();
			changeLightPosition();
			if (keyboard->isKeyPressed(GLFW_KEY_ESCAPE))
			{
				this->setState(GAME_MENU);
			}
		}
	}
	else if (state == GAME_MENU)
	{
		GameObject * newCollider = PlayerMovementManager::getLastCollider();
		removeTransparencyIfAlreadyMoved(newCollider, lastCollider);
		static int counter = 0;
		menu->update();
		if (this->state == GAME_ACTIVE)
		{
			lastCollider = nullptr;
			counter = 0;
			return;
		}
		getPlayer()->update();
		MOVEMENT_STATUS status;
		switch (counter / 4)
		{
			case 0:
			{
				status = PlayerMovementManager::tryMoveLeft(getPlayer(), manager);
			}break;
			case 1:
			{
				status = PlayerMovementManager::tryMoveBackward(getPlayer(), manager);
			}break;
			case 2:
			{
				status = PlayerMovementManager::tryMoveRight(getPlayer(), manager);
			}break;
			case 3:
			{
				status = PlayerMovementManager::tryMoveForward(getPlayer(), manager);
			}break;
			case 4:
			{
				status = MOVE_NOT_MOVING_COLLISION;
				counter = 0;
			}
		}
		if (status == MOVE_MOVING && lastCollider != nullptr)
			lastCollider->setAlpha(1.f);

		lastCollider = PlayerMovementManager::getLastCollider();
		setTransparencyIfMovingThrough(lastCollider, status);
		if (status == MOVE_MOVING)
			counter++;
		if (status == MOVE_MOVING_HOLE)
			counter+=2;
	}
}
bool Game::winIfAtWhiteHole()
{
	WhiteHole * hole = manager->getWhiteHole();
	if (getPlayer()->isAtPositionNeighborhood(hole->getPosition()))
	{
		manager->addMask(glm::fvec3(0.5f, 0.7f, 0.5f));
		current_info_text = string("You won! Congratulations!");
		if (keyboard->isAnythingPressed())
		{
			this->setState(GAME_MENU);
		}
		return true;
	}
	return false;
}
void Game::close()
{
	glfwSetWindowShouldClose(Window::getGLFWWindow(), GL_TRUE);
}
void Game::changeLightPosition()
{
	glm::fvec3 newLightPos = getPlayer()->getPosition();
	newLightPos.y = 1.5f;
	newLightPos.z += 2.5f;
	manager->getLight()->setPosition(newLightPos);
}
void Game::lose()
{
	current_error_text = "You lost! Try again";
	if (keyboard->isAnythingPressed())
	{
		this->setState(GAME_MENU);
	}

}
void Game::endGameIfOutOfField()
{
	glm::fvec2 pos = glm::fvec2(getPlayer()->getPosition().x, getPlayer()->getPosition().z);
	if (manager->getField()->isInField(pos) == false)
		glfwSetWindowShouldClose(Window::getGLFWWindow(), GL_TRUE);
}

void Game::render()
{
	if (state == GAME_ACTIVE)
	{
		manager->renderAll();
		writePlayerPosition();
	}
	else if (state == GAME_MENU)
	{
		//StaticShader shader = StaticShader();
		manager->renderAll();
		//menu->render(&Renderer(shader), shader);
	}
	Window::update();
}

void Game::checkInputKeysAndMovePlayer()
{
	GameObject * newCollider = PlayerMovementManager::getLastCollider();
	
	MOVEMENT_STATUS status = PlayerMovementManager::checkInputKeysForMovement(getPlayer(), manager);
	//removeTransparencyIfAlreadyMoved(newCollider, lastCollider);
	//if(status == MOVE_MOVING)
	if (status == MOVE_NOT_MOVING_COLLISION)
		this->manager->shake(2.0f);
	if (status != MOVE_MOVING_HOLE && status != MOVE_ALREADY_MOVING && lastCollider != nullptr)
		lastCollider->setAlpha(1.f);
	newCollider = PlayerMovementManager::getLastCollider();
	if (newCollider != nullptr)
		lastCollider = newCollider;
	setTransparencyIfMovingThrough(lastCollider, status);
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
	settings->font->renderText((GLchar *)current_info_text.c_str(), message_info_pos, glm::fvec3(0.2f, 0.6f, 1.0f), 1.2f);
	sprintf(debugInfo, "X : %3.2f, Y : %3.2f, Z : %3.2f", getPlayer()->getPosition().x, getPlayer()->getPosition().y, getPlayer()->getPosition().z);
	settings->font->renderText(debugInfo, glm::fvec2(0.f, 0.f), glm::fvec3(1.0f, 0.1f, 0.1f), 1.0f);
}
Game::~Game()
{
	puts("IM DYING!!");
	delete manager;
	delete loader;
	delete settings;
	Window::close();
}
bool Game::isEnoughEnergy()
{
	return getPlayer()->getEnergy() > 0.3f;
}
void window_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_F1)
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