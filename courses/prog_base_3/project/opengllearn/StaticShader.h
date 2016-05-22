#pragma once
#include "MainHeaders.h"
#include "Shader.h"
#include "Camera.h"
#include "Light.h"
class StaticShader : public Shader
{
	private:
		GLuint location_transofrmationMatrix;
		GLuint location_projectionMatrix;
		GLuint location_viewMatrix;
		GLuint location_lightPosition;
		GLuint location_lightColor;
		GLuint location_alpha;
		GLuint location_shake;
		GLuint location_time;
		GLuint location_mask;
	public:
		StaticShader(); // Actually just constatnt paths // EDITED
		void loadTransformationMatrix(glm::mat4 matrix);
		void loadProjectionMatrix(glm::mat4 matrix);
		void loadViewMatrix(Camera  *camera);
		void loadLight(Light * light);
		void loadAlpha(GLfloat alpha);
		void loadShake(GLboolean shake, GLfloat time);
		void loadMask(glm::fvec3 mask);
	protected:
		virtual void bindAttributes() override;
		virtual void getAllUniformLocations() override;

};