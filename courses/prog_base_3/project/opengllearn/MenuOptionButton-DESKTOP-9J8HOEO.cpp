#include "MenuOptionButton.h"

MenuOptionButton::MenuOptionButton(Loader * loader, Font * font, glm::fvec3 color, string text) : MenuOption(font, GuiTexture(), color, text)
{
	static GLuint id = loader->loadTexture("models\\menu\\button\\button.png");
	texture = GuiTexture(id, glm::fvec2(), glm::fvec2(0.19f * 2, 0.045f * 3));
	alpha = 0.8f;
}