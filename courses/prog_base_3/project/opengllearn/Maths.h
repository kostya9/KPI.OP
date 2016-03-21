#pragma once
#include "MainHeaders.h"	
class Maths
{
	public:
		static glm::mat4 createTransformationMatrix(glm::vec3 translation, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat scale)
		{
			glm::mat4 matrix = glm::mat4(); // IDENTITY MATRIX;
			glm::translate(matrix, translation);
			glm::rotate(matrix, glm::radians(rx), glm::vec3(1, 0, 0));
			glm::rotate(matrix, glm::radians(ry), glm::vec3(0, 1, 0));
			glm::rotate(matrix, glm::radians(rz), glm::vec3(0, 0, 1));
			glm::scale(matrix, glm::vec3(scale, scale, scale));
			return matrix;
		}
};