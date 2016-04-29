#pragma once
#include "Window.h"
#include "Keyboard.h"
#include "Settings.h"
#include "GameObjectManager.h"
#include "Field.h"
#include "Player.h"
// TODO : to implement interface functions
enum GameState { GAME_MENU, GAME_ACTIVE };

class Game
{
	public:
		Game();
		void generateField(glm::fvec2 center, GLuint size);
		void createPlayer(glm::fvec2 position);
		void createWall(glm::fvec2 position);
		void createLight(GLfloat brightness, glm::fvec3 position);
		Keyboard * getKeyboard();
		Player * getPlayer();
		void update();
		void render();
		~Game();
	private:
		const glm::fvec2 message_error_pos = glm::fvec2(00.f, 500.f);
		string current_error_text;
		GameState State;
		Light * light;
		Player * player;
		Loader * loader;
		Renderer * renderer;
		StaticShader * shader;
		Keyboard * keyboard;
		Settings * settings;
		GameObjectManager * manager;

};