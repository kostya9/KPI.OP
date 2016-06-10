#pragma once
#include "MenuOptionButton.h"
#include "GameDescriptionScreen.h"

class GameDescriptionButton : public MenuOptionButton
{
private:
	GameDescriptionScreen * s;
public:
	GameDescriptionButton(Loader * loader, Font * font, glm::fvec3 colo);
	int onClick();
};
