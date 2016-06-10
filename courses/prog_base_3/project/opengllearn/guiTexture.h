#pragma once
#include "MainHeaders.h"
class GuiTexture
{
private:
	GLuint texture;
	glm::fvec2 position;
	glm::fvec2 scale;
	GLfloat scalePlus = 1.0f;
public:
	GuiTexture() {}
	GuiTexture(int texture, glm::fvec2 position, glm::fvec2 scale)
	{
		this->texture = texture;
		this->position = position;
		this->scale = scale;
	}
	GLuint getTexture() { return texture; }
	glm::fvec2 getScale() { return scale * scalePlus; }
	glm::fvec2 getPosition() { return position; }
	void setPosition(glm::fvec2 pos);
	void setScale(GLfloat scale);
	void setInitialScale(glm::fvec2 scale);


};
