#include "MenuOptionSlider.h"

MenuOptionSlider::MenuOptionSlider(Loader * loader, Font * font, glm::fvec3 color) : MenuOption(font, GuiTexture(), color, string(""))
{
	static GLuint id = loader->loadTexture("models\\menu\\slider\\yellow_sliderLeft.png");
	texture = GuiTexture(id, glm::fvec2(), glm::fvec2(0.1f, 0.3f));
}