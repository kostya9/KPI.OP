#include "HighScore.h"
#include "Menu.h"
#include "HighScoreScreen.h"

HighScore::HighScore(Loader * loader, Font * font, glm::fvec3 color) : MenuOptionButton(loader, font, color, string("High Scores"))
{
	this->scale = 1.2f;
	this->id = 102;
	this->screen = new HighScoreScreen(loader, font, color);
}

int HighScore::onClick()
{
	this->menu->setFullScreen(screen);
	return OK;
}
