#pragma once
#include "MenuOptionButton.h"

class HighScoreScreen : public MenuOptionButton
{
public:
	HighScoreScreen(Loader * loader, Font * font, glm::fvec3 color);
	int onClick() override;
	void onSelect() override;
};
