#pragma once
#include "Window.h"
#include "Keyboard.h"
#include "Settings.h"
#include "GameObjectManager.h"
#include "PlayerMovementManager.h"
#include "GameObjectLoader.h"
#include "Field.h"
#include "Player.h"
#include "Menu.h"
#include "MenuOptionButton.h"
#include "MenuOptionSlider.h"
// TODO : to implement interface functions
enum GameState { GAME_MENU, GAME_ACTIVE };

class Game
{
	public:
		Game();
		Keyboard * getKeyboard();
		Player * getPlayer();
		Field * getField();
		void setState(GameState state);
		void cleanGameObjects();
		void loadLevel(string path);
		void generateField(glm::fvec2 center, GLuint size);
		void createPlayer(glm::fvec2 position);
		void createWall(glm::fvec2 position);
		void createLight(GLfloat brightness, glm::fvec3 position);
		void createWhiteHole(glm::fvec2 position);
		void update();
		void changeLightPosition();
		void endGameIfOutOfField();
		void winIfAtWhiteHole();
		void close();
		void checkInputKeysAndMovePlayer();
		void removeTransparencyIfAlreadyMoved(GameObject * newCollider, GameObject * collider);
		void updatingErrorMessage(MOVEMENT_STATUS status);
		void setTransparencyIfMovingThrough(GameObject * collider, MOVEMENT_STATUS status);
		void render();
		void writePlayerPosition();
		~Game();
	private:
		const glm::fvec2 message_error_pos = glm::fvec2(00.f, 500.f);
		string current_error_text;
		GameState state;
		GameObjectLoader * loader;
		Keyboard * keyboard;
		Settings * settings;
		Menu * menu;
		GameObjectManager * manager;
		GameObject * lastCollider;

};