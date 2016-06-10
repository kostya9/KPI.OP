#pragma once
#include "MainHeaders.h"
class GuiTexture
{
private:
	GLuint texture;
	glm::fvec2 position;
	glm::fvec2 scale;
public:
	GuiTexture(int texture, glm::fvec2 position, glm::fvec2 scale)
	{
		this->texture = texture;
		this->position = position;
		this->scale = scale;
	}

	GLuint getTexture() { return texture; }
	glm::fvec2 getScale() { return scale; }
	glm::fvec2 getPosition() { return position; }


};
