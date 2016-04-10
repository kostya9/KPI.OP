#pragma once
#include "MainHeaders.h"
#include "Shader.h"
#include "Camera.h"
class StaticShader : public Shader
{
	private:
		GLuint location_transofrmationMatrix;
		GLuint location_projectionMatrix;
		GLuint location_viewMatrix;
	public:
		StaticShader(); // Actually just constatnt paths // EDITED
		void loadTransformationMatrix(glm::mat4 matrix);
		void loadProjectionMatrix(glm::mat4 matrix);
		void loadViewMatrix(Camera camera);
	protected:
		virtual void bindAttributes() override;
		virtual void getAllUniformLocations() override;

};