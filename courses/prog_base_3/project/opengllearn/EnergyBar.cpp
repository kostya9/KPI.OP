#include "EnergyBar.h"

EnergyBar::EnergyBar(glm::fvec2 position, Loader *loader, Font* font)
{
	this->font = font;
	GLuint id = loader->loadTexture("models\\bar256x256.png");
	GLuint back_id = loader->loadTexture("models\\bar_back256x256.bmp");
	this->barTexture = GuiTexture(id, position, glm::fvec2(0.255f, 0.128f));
	this->backTexture = GuiTexture(back_id, position, glm::fvec2(0.255f, 0.128f));
	length = 2.1f * 0.255f;
	energy = 1.0f;
}

void EnergyBar::setEnergy(GLfloat energy)
{
	this->energy = energy;
}

void EnergyBar::renderText()
{
	glm::fvec2 pos = glm::fvec2((1 + barTexture.getPosition().x - length/2 + 0.05f) / 2 * Window::getWidth(), (1 + barTexture.getPosition().y - 0.02f) / 2 * Window::getHeight());
	font->renderText("Energy", pos, glm::fvec3(1.0f, 1.0f, 1.0f), 1.0f);
}

GLfloat EnergyBar::getXMax()
{
	return barTexture.getPosition().x - length/2 + length * energy * energy;
}

GuiTexture EnergyBar::getBarTexture()
{
	return barTexture;
}

GuiTexture EnergyBar::getBackTexture()
{
	return backTexture;
}
