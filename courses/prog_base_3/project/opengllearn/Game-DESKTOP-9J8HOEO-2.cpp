#define  _CRT_SECURE_NO_WARNINGS
#include "guiTexture.h"
#include "GuiRenderer.h"
#include "Game.h"
#include "PlayerMovementManager.h"
#include <Windows.h>
void onMouseButton(GLFWwindow* window, int button, int action, int mode);
void window_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

Game::Game()
{
	ifstream f(stats_file_name);
	if (f.good())
	{
		f.close();
		points = new Points(stats_file_name);
	}
	else
		points = new Points();

	Window::open();
	manager = new GameObjectManager();
	settings = new Settings();
	settings->font = new Font("fonts/Open_sans/OpenSans-Regular.ttf");
	loader = new GameObjectLoader(manager, settings->font);
	keyboard = new Keyboard();
	Light* light = new Light(glm::fvec3(0.0f, 0.0f, 0.0f), glm::fvec3(1.0f, 1.0f, 1.0f));
	manager->addObject(light);
	key_callback kb = window_key_callback;
	glfwSetMouseButtonCallback(Window::getGLFWWindow(), onMouseButton);
	Window::addCallBack(kb);
	setState(GAME_MENU);
	loader->loadMenu(this);
	PlaySound(TEXT("1.wav"), NULL, SND_ASYNC | SND_LOOP);
}

void onMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (action == GLFW_PRESS)
		{
			keyboard->leftButtonPress();
		}
		else if (action == GLFW_RELEASE)
		{
			keyboard->leftButtonRelease();
		}
	}
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

Keyboard* Game::getKeyboard()
{
	return keyboard;
}

Player* Game::getPlayer()
{
	return manager->getPlayer();
}

Field* Game::getField()
{
	return manager->getField();
}

Points* Game::getPoints()
{
	return points;
}

void Game::setState(GameState state)
{
	cleanGameObjects();
	this->state = state;
	if (state == GAME_MENU)
	{
		PlaySound(TEXT("menu.wav"), NULL, SND_ASYNC | SND_LOOP);
		points->serialize(stats_file_name);
		loader->generateField(glm::fvec2(0.0f, 0.0f), 7);
		loader->createPlayer(glm::fvec2(2.0f, -2.0f));
		loader->createWall(glm::fvec2(-2.0f, 0.f));
		loader->createWall(glm::fvec2(2.0f, 0.f));
		loader->createShadow(getPlayer()->getPosition());
		loader->loadMenu(this);
	}
	else
	{
		PlaySound(TEXT("1.wav"), NULL, SND_ASYNC | SND_LOOP);
		levelStartTime = glfwGetTime();
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
	loader = new GameObjectLoader(manager, settings->font);
	Light* light = new Light(glm::fvec3(0.0f, 0.0f, 0.0f), glm::fvec3(1.0f, 1.0f, 1.0f));
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
	static int counter = 0;
	if (state == GAME_ACTIVE)
	{
		//Menu vars
		counter = 0;
		lastCollider = nullptr;

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
			{
				//PlaySound(TEXT("hit.wav"), NULL, SND_ASYNC);
				Beep(750, 10);
				getPlayer()->startDamaging(100);
				this->manager->blinkMask(glm::fvec3(242 / 255.0f, 188 / 255.f, 188 / 255.f));
			}
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
		GameObject* newCollider = PlayerMovementManager::getLastCollider();
		removeTransparencyIfAlreadyMoved(newCollider, lastCollider);
		getPlayer()->update();
		MOVEMENT_STATUS status = MOVE_NOT_MOVING_NO_COMMANDS;
		switch (counter / 4)
		{
		case 0:
			{
				status = PlayerMovementManager::tryMoveLeft(getPlayer(), manager);
			}
			break;
		case 1:
			{
				status = PlayerMovementManager::tryMoveBackward(getPlayer(), manager);
			}
			break;
		case 2:
			{
				status = PlayerMovementManager::tryMoveRight(getPlayer(), manager);
			}
			break;
		case 3:
			{
				status = PlayerMovementManager::tryMoveForward(getPlayer(), manager);
			}
			break;
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
			counter += 2;
	}
}

bool Game::winIfAtWhiteHole()
{
	WhiteHole* hole = manager->getWhiteHole();
	if (getPlayer()->isAtPositionNeighborhood(hole->getPosition()))
	{
		static bool set = false;
		if (set == false)
		{
			PlaySound(TEXT("yay.wav"), NULL, SND_ASYNC);
			delete keyboard;
			keyboard = new Keyboard;
			this->keyboard = keyboard;
			if (levelStartTime != 0)
				curPoints = 1000 / (glfwGetTime() - levelStartTime);
			// ReSharper disable once CppAssignedValueIsNeverUsed
			set = true;
		}

		// TODO propper once management and refactor
		manager->addMask(glm::fvec3(0.5f, 0.7f, 0.5f));

		current_info_text = string("You won! Congratulations!\n You got " + to_string(curPoints) + " points");
		if (keyboard->isAnythingPressed())
		{
			set = false;
			if (curPoints != 0)
				points->addEntry(curPoints);
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
	static bool initialised = false;
	if (!initialised)
	{
		delete keyboard;
		keyboard = new Keyboard;
		this->keyboard = keyboard;
		initialised = true;
	}
	current_error_text = "You lost! Try again";
	if (keyboard->isAnythingPressed())
	{
		initialised = false;
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
	GameObject* newCollider;

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

void Game::removeTransparencyIfAlreadyMoved(GameObject* newCollider, GameObject* collider)
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
		//current_error_text = string("Could not move - collision detected");
	}
	else if (status == MOVE_NOT_ENOUGH_ENERGY)
	{
		this->manager->shake(2.0f);
		current_error_text = string("Not enough energy");
	}
	else if (status != MOVE_NOT_MOVING_NO_COMMANDS)
	{
		current_error_text = string("");
	}
}

void Game::setTransparencyIfMovingThrough(GameObject* collider, MOVEMENT_STATUS status)
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
	//char debugInfo[100];
	settings->font->renderText(const_cast<GLchar *>(current_error_text.c_str()), message_error_pos, glm::fvec3(1.0f, 0.1f, 0.1f), 1.0f);
	settings->font->renderText(const_cast<GLchar *>(current_info_text.c_str()), message_info_pos, glm::fvec3(0.2f, 0.6f, 1.0f), 1.2f);
	/*sprintf(debugInfo, "X : %3.2f, Y : %3.2f, Z : %3.2f", getPlayer()->getPosition().x, getPlayer()->getPosition().y, getPlayer()->getPosition().z);
	settings->font->renderText(debugInfo, glm::fvec2(0.f, 0.f), glm::fvec3(1.0f, 0.1f, 0.1f), 1.0f);/**/
}

Settings* Game::getSettings()
{
	return this->settings;
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
