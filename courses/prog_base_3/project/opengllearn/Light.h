#pragma once
#include "MainHeaders.h"
class Light {
private:
	glm::vec3 position;
	glm::vec3 color;
public:
	Light(glm::vec3 position, glm::vec3 color)
	{
		this->position = position;
		this->color = color;
	}
	glm::vec3 getPosition() {
		return position;
	}
	glm::vec3 getColor() {
		return color;
	}
	void setPosition(glm::vec3 position) {
		this->position = position;
	}
	void setColor(glm::vec3 color) {
		this->color = color;
	}
};