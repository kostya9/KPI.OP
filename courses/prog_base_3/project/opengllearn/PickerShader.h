#pragma once
#include "Shader.h"
class PickerShader : public Shader{
private:

	GLuint location_transformationMatrix;
	GLuint location_pickerColor;
public:
	PickerShader() : Shader("shaders\\picker\\vertex.sh", "shaders\\picker\\fragment.sh") {
		getAllUniformLocations();
		bindAttributes();
	};
	void loadTransformation(glm::fmat4 matrix) {
		this->loadMatrix(location_transformationMatrix, matrix);
	}
	void loadPickerColor(glm::fvec3 color)
	{
		this->loadVector(location_pickerColor, color);
	}
protected:
	void getAllUniformLocations() {
		location_transformationMatrix = this->getUniformLocation("transformationMatrix");
		location_pickerColor = this->getUniformLocation("pickerColor");
	}
	void bindAttributes()
	{
		this->bindAttribute(0, "position");
	}
};