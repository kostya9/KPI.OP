#pragma once
#include "guiTexture.h"
#include "Loader.h"
#include "Font.h"
class EnergyBar {
private:
	GuiTexture backTexture;
	GuiTexture barTexture;
	GLfloat energy;
	GLfloat length;
	Font * font;
public:
	EnergyBar(glm::fvec2 position, Loader *loader, Font * font);
	void setEnergy(GLfloat energy);
	void renderText();
	GLfloat getXMax();
	GuiTexture getBarTexture();
	GuiTexture getBackTexture();
};