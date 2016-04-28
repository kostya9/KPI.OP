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

void StaticShader::loadLight(Light light)
{
	loadVector(location_lightColor, light.getColor());
	loadVector(location_lightPosition, light.getPosition());
}

void StaticShader::loadAlpha(GLfloat alpha)
{
	loadFloat(location_alpha, alpha);
}

void StaticShader::bindAttributes() // DO NOT INLINE THIS AND ATTRIBUTE
{
	Shader::bindAttribute(0, "position");
	Shader::bindAttribute(1, "textureCoordinates");
	Shader::bindAttribute(2, "normal");
}

void StaticShader::getAllUniformLocations()
{
	location_transofrmationMatrix = this->getUniformLocation("transformationMatrix");
	location_projectionMatrix = this->getUniformLocation("projectionMatrix");
	location_viewMatrix = this->getUniformLocation("viewMatrix");
	location_lightPosition = this->getUniformLocation("lightPosition");
	location_lightColor = this->getUniformLocation("lightColor");
	location_alpha = this->getUniformLocation("alpha");
}
