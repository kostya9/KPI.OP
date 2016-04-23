#pragma once
#include "Keyboard.h"
#include "Settings.h"
// TODO : to implement interface functions
enum GameState { GAME_MENU, GAME_ACTIVE };

class Game
{
	public:
		GameState State;
		Keyboard * keyboard;
		Settings * settings;
		Game(GLuint width, GLuint heght);
	private:

};