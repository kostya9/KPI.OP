#pragma once
#include "MainHeaders.h"
#include "Engine.h"
struct Entity
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
		Entity(TexturedModel model)
		{
			this->model = model;
			this->position = glm::vec3(0.0f, 0.0f, 0.0f);
			this->rotX = 0.0f;
			this->rotY = 0.0f;
			this->rotZ = 0.0f;
			this->scale = 1.0f;
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