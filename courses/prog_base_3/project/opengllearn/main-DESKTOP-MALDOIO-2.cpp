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
	//Font * font = new Font("fonts/Open_sans/OpenSans-Regular.ttf");
	//char debugInfo[100];*/
	while (!glfwWindowShouldClose(Window::getGLFWWindow()))
	{
		//sprintf(debugInfo, "X : %3.2f, Y : %3.2f, Z : %3.2f", game->getPlayer()->getPosition().x, game->getPlayer()->getPosition().y, game->getPlayer()->getPosition().z);
		//font->renderText(debugInfo, glm::fvec2(100.f, 10.f), glm::fvec3(1.0f, 0.1f, 0.1f), 100.0f);		
		game->render();
		game->update();
	}
	//delete font;
	delete game;
	_getch();
	return 0;
}