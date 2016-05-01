#pragma once
#include "MainHeaders.h"
#include "GameObject.h"

class Field : public GameObject
{
	private:
		GLuint size;
		const char * fieldPath = "../opengllearn/models/field/field.obj";
	public:
		// Generates a field size x size
		Field(Loader * loader, GLuint size, glm::vec3 position);
		bool isInField(glm::fvec2 position);
		GLuint getSize();
};