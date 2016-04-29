#define _CRT_SECURE_NO_WARNINGS
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
	game->generateField(glm::fvec2(0.0f, 0.0f), 3);
	game->createPlayer(glm::fvec2(0.0f, 0.0f));
	game->createLight(1.0f, glm::fvec3(0.0f, 2.0f, 1.0f));
	game->createWall(glm::fvec2(1.0f, 0.0f));

	Font * font = new Font("fonts/Open_sans/OpenSans-Regular.ttf");
	char debugInfo[100];
	while (!glfwWindowShouldClose(Window::getGLFWWindow()))
	{
		//setSineHoleAppearance(manager->wall);
		sprintf(debugInfo, "X : %3.2f, Y : %3.2f, Z : %3.2f", game->getPlayer()->getPosition().x, game->getPlayer()->getPosition().y, game->getPlayer()->getPosition().z);
		font->renderText(debugInfo, glm::ivec2(12, 43), glm::vec3(0.1f, 0.1f, 0.1f), 1.0f);
		game->render();
	}
	delete font;
	delete game;
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