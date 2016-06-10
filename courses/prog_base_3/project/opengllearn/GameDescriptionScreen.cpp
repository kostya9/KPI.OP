#include "GameDescriptionScreen.h"
#include "Menu.h"
GameDescriptionScreen::GameDescriptionScreen(Loader * loader, Font * font, glm::fvec3 color) : MenuOptionButton(loader, font, color, string("High Scores"))
{
	GLuint id = loader->loadTexture("models\\gameDescription.jpg");
	this->texture = GuiTexture(id, glm::fvec2(0, 0), glm::fvec2(0.95f, 0.75f));
}

int GameDescriptionScreen::onClick()
{
	this->menu->deleteFullSreen();
	return OK;
}
