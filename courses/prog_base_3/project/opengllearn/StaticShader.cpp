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

void StaticShader::bindAttributes() // DO NOT INLINE THIS AND ATTRIBUTE
{
	Shader::bindAttribute(0, "position");
	Shader::bindAttribute(1, "textureCoordinate");
}

void StaticShader::getAllUniformLocations()
{
	location_transofrmationMatrix = this->getUniformLocation("transformationMatrix");
}
