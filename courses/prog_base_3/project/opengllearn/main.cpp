﻿#define _CRT_SECURE_NO_WARNINGS
#include "MainHeaders.h"
#include "Keyboard.h"
#include "cstdio"
#include "Player.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Font.h"
#include "Game.h"

Keyboard * keyboard;
// The MAIN function, from here we start the application and run the game loop
int main()
{
	Game * game = new Game();
	keyboard = game->getKeyboard();
	game->generateField(glm::fvec2(0.0f, 0.0f), 7);
	game->createPlayer(glm::fvec2(0.0f, 0.0f));
	game->createLight(1.2f, glm::fvec3(0.0f, 2.0f, 1.0f));
	game->createWall(glm::fvec2(1.0f, 0.0f));
	game->createWall(glm::fvec2(2.0f, 0.0f));
	game->createWall(glm::fvec2(1.0f, -2.0f));
	//bool test = game->getField()->isInField(glm::fvec2(-2.0f, -2.0f));
	//printf("Test is %s", test == true ? "true" : "false");
	Font * font = new Font("fonts/Open_sans/OpenSans-Regular.ttf");
	char debugInfo[100];
	while (!glfwWindowShouldClose(Window::getGLFWWindow()))
	{
		//setSineHoleAppearance(manager->wall);
		sprintf(debugInfo, "X : %3.2f, Y : %3.2f, Z : %3.2f", game->getPlayer()->getPosition().x, game->getPlayer()->getPosition().y, game->getPlayer()->getPosition().z);
		font->renderText(debugInfo, glm::fvec2(100.f, 10.f), glm::fvec3(1.0f, 0.1f, 0.1f), 100.0f);
		game->update();
		game->render();
	}
	delete font;
	delete game;
	_getch();
	return 0;
}


/*void setSineHoleAppearance(Wall * wall)
{
	GLfloat hole = glm::sin(glfwGetTime());
	if (hole > 0.1)
		wall->showHole(WallHole::HOLE_DIRECTION_Z);
	else
		wall->hideHole();
}/**/