#include "StaticShader.h"


// Actually just constatnt paths // EDITED

StaticShader::StaticShader() : Shader("shaders/vertex.sh", "shaders/fragment.sh")
{
	getAllUniformLocations();
}

void StaticShader::loadTransformationMatrix(glm::mat4 matrix)
{
	Shader::loadMatrix(location_transofrmationMatrix, matrix);
}

void StaticShader::loadProjectionMatrix(glm::mat4 matrix)
{
	this->loadMatrix(location_projectionMatrix, matrix);
}

void StaticShader::loadViewMatrix(Camera camera)
{
	glm::mat4 viewMatrix = camera.getViewMatrix();
	this->loadMatrix(location_viewMatrix, viewMatrix);
}

void StaticShader::bindAttributes() // DO NOT INLINE THIS AND ATTRIBUTE
{
	Shader::bindAttribute(0, "position");
	Shader::bindAttribute(1, "textureCoordinate");
}

void StaticShader::getAllUniformLocations()
{
	location_transofrmationMatrix = this->getUniformLocation("transformationMatrix");
	location_projectionMatrix = this->getUniformLocation("projectionMatrix");
	location_viewMatrix = this->getUniformLocation("viewMatrix");
}
