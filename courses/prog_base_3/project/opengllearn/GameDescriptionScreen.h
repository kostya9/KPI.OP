#pragma once
#pragma once
#include "MenuOptionButton.h"

class GameDescriptionScreen : public MenuOptionButton
{
public:
	GameDescriptionScreen(Loader * loader, Font * font, glm::fvec3 color);
	int onClick() override;
};
