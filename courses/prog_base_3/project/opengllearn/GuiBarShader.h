#pragma once
#include "MainHeaders.h"
#include "Shader.h"
class GuiBarShader : public Shader {
private:

	GLuint location_transformationMatrix;
	GLuint location_xMax;
	GLuint location_yMax;
public:
	GuiBarShader() : Shader("shaders\\gui\\bar\\vertex.sh", "shaders\\gui\\bar\\fragment.sh") {
		getAllUniformLocations();
		bindAttributes();
	};
	void loadTransformation(glm::fmat4 matrix) {
		this->loadMatrix(location_transformationMatrix, matrix);
	}
	void loadXMax(GLfloat xMax)
	{
		this->loadFloat(location_xMax, xMax);
	}
	void loadYMax(GLfloat yMax)
	{
		this->loadFloat(location_yMax, yMax);
	}
protected:
	void getAllUniformLocations() {
		location_transformationMatrix = this->getUniformLocation("transformationMatrix");
		location_xMax = this->getUniformLocation("xMax");
		location_yMax = this->getUniformLocation("yMax");
	}
	void bindAttributes()
	{
		this->bindAttribute(0, "position");
	}
};