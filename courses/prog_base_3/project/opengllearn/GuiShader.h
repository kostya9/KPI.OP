#pragma once
#include "MainHeaders.h"
#include "Shader.h"
class GuiShader : public Shader {
private:

	GLuint location_transformationMatrix;
	GLuint location_extraIDColor;
public:
	GuiShader() : Shader("shaders\\gui\\vertex.sh", "shaders\\gui\\fragment.sh") {
		getAllUniformLocations();
		bindAttributes();
	};
	void loadTransformation(glm::fmat4 matrix) {
		this->loadMatrix(location_transformationMatrix, matrix);
	}
protected:
	void getAllUniformLocations() {
		location_transformationMatrix = this->getUniformLocation("transformationMatrix");	
	}
	void bindAttributes()
	{
		this->bindAttribute(0, "position");
	}
};