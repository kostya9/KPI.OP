#pragma once
#include "MainHeaders.h"	
class Maths
{
	public:
		static glm::mat4 createTransformationMatrix(glm::vec3 translation, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat scale)
		{
			glm::mat4 matrix = glm::mat4(); // IDENTITY MATRIX;
			matrix = glm::translate(matrix, translation);
			if(rx != 0)
				matrix = glm::rotate(matrix, glm::radians(rx), glm::vec3(1, 0, 0));
			if(ry != 0)
				matrix = glm::rotate(matrix, glm::radians(ry), glm::vec3(0, 1, 0));
			if(rz != 0)
				matrix = glm::rotate(matrix, glm::radians(rz), glm::vec3(0, 0, 1));
			matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));
			return matrix;
		}
		static glm::fmat4 createTransformationMatrix(glm::fvec2 translation, glm::fvec2 scale) {
			glm::fmat4 matrix = glm::fmat4();
			matrix = glm::translate(matrix, glm::fvec3(translation.x, translation.y, 0.0f));
			matrix = glm::scale(matrix, glm::fvec3(scale.x, scale.y, 1.f));
			return matrix;
		}
};