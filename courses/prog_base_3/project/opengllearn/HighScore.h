#pragma once
#include "MenuOption.h"
#include "MenuOptionButton.h"
#include "HighScoreScreen.h"

class HighScore : public MenuOptionButton
{
private:
	HighScoreScreen *screen;
public:
	HighScore(Loader * loader, Font * font, glm::fvec3 color);
	int onClick() override;
};
