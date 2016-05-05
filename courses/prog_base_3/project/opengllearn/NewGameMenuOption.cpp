#include "NewGameMenuOption.h"
#include "Game.h"
NewGameMenuOption::NewGameMenuOption(Loader * loader, Font * font, glm::fvec3 color) : MenuOptionButton(loader, font, color, string("New Game"))
{
	this->scale = 1.2f;
}

void NewGameMenuOption::onClick()
{
	system("genRandomLevel.bat");
	menu->getGame()->cleanGameObjects();
	menu->getGame()->setState(GAME_ACTIVE);
	menu->getGame()->loadLevel(string("levels/output.txt"));
}
