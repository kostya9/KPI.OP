#include "ExitMenuOption.h"
#include "Game.h"
ExitMenuOption::ExitMenuOption(Loader * loader, Font * font, glm::fvec3 color) : MenuOptionButton(loader, font, color, string("Exit"))
{
}

void ExitMenuOption::onClick()
{
	menu->getGame()->close();
}