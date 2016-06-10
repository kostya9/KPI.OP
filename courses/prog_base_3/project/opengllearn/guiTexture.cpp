#include "guiTexture.h"
#include <glm/detail/type_mat.hpp>

void GuiTexture::setPosition(glm::fvec2 pos)
{
	this->position = pos;
}

void GuiTexture::setScale(GLfloat scale)
{
	this->scalePlus = scale;
}

void GuiTexture::setInitialScale(glm::fvec2 scale)
{
	this->scale = scale;
}
