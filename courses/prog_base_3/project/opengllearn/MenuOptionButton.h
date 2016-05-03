#pragma once
#include "MenuOption.h"
class MenuOptionButton : public MenuOption
{
	public:
		MenuOptionButton(Loader * loader, Font * font, glm::fvec3 color, string text);
};