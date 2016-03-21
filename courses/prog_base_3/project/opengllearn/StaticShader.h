#pragma once
#include "MainHeaders.h"
#include "Shader.h"
class StaticShader : public Shader
{
	private:
		GLuint location_transofrmationMatrix;
	public:
		StaticShader(); // Actually just constatnt paths // EDITED
		void loadTransformationMatrix(glm::mat4 matrix);
	protected:
		virtual void bindAttributes() override;
		virtual void getAllUniformLocations() override;

};