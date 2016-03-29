#pragma once
#include "MainHeaders.h"
#include "Engine.h"
class Entity
{
	public:
		TexturedModel model;
		glm::vec3 position;
		GLfloat rotX, rotY, rotZ;
		GLfloat scale;
		Entity(TexturedModel model, glm::vec3 position, float rotX, float rotY, float rotZ, float scale)
		{
			this->model = model;
			this->position = position;
			this->rotX = rotX;
			this->rotY = rotY;
			this->rotZ = rotZ;
			this->scale = scale;
		}
		void increasePosition(GLfloat dx, GLfloat dy, GLfloat dz)
		{
			position.x += dx;
			position.y += dy;
			position.z += dz;
		}
		void increaseRotation(GLfloat dx, GLfloat dy, GLfloat dz)
		{
			rotX += dx;
			rotY += dy;
			rotZ += dz;
		}

};