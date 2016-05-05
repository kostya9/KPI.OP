#pragma once
#include "MenuOptionButton.h"
class ExitMenuOption : public MenuOptionButton
{
	public:
		ExitMenuOption(Loader * loader, Font * font, glm::fvec3 colo);
		void onClick();
};