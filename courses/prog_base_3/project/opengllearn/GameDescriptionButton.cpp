#include "GameDescriptionButton.h"
#include "Menu.h"
GameDescriptionButton::GameDescriptionButton(Loader * loader, Font * font, glm::fvec3 colo) : MenuOptionButton(loader, font, color, string("How to play"))
{
	this->id = 104;
	s = new GameDescriptionScreen(loader, font ,color);
}

int GameDescriptionButton::onClick()
{
	this->menu->setFullScreen(s);
	return OK;
}
