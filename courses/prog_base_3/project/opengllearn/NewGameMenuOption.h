#pragma once
#include "MenuOptionButton.h"
class NewGameMenuOption : public MenuOptionButton
{
	public:
		NewGameMenuOption(Loader * loader, Font * font, glm::fvec3 color);
		void onClick();
};