#pragma once
#include "MainHeaders.h"
#include "StaticShader.h"
#include "TexturedModel.h"
#include "Model.h"
#include "Entity.h"
class Renderer
{
private:
	const GLfloat FOV = 70.0f;
	const GLfloat NEAR_PLANE = 0.1f;
	const GLfloat FAR_PLANE = 100.0f;
	glm::mat4 projectionMatrix;
	void createProjectionMatrix()
	{
		projectionMatrix = glm::perspective(FOV, 1.0f, NEAR_PLANE, FAR_PLANE);
		//projectionMatrix = glm::ortho(0.0f, (float)Window::getHeight(), 0.0f, (float)Window::getWidth()/*, NEAR_PLANE, FAR_PLANE*/);
	}
	public:
		Renderer(StaticShader shader)
		{
			createProjectionMatrix();
			shader.use();
			shader.loadProjectionMatrix(projectionMatrix);
			shader.unUse();
		}
		/*Prepares the window for drawing the next frame*/
		void prepare()
		{
			glfwPollEvents();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.6784f, 0.792f, 0.99f, 1.0f); // LIGHT BLUE 
		}
		void render(Entity entity, StaticShader shader)
		{
			render(entity, shader, 1.0f);

		}
		/*Renders(draws) a model to the screen*/
		void render(Entity entity, StaticShader shader, GLfloat alpha)
		{
			if (alpha != 1.0f)
			{
				glEnable(GL_BLEND);
				glEnable(GL_CULL_FACE);
			}
			TexturedModel texturedModel = entity.model;
			Model model = texturedModel.getModel();
			Texture texture = texturedModel.getTexture();
			GLuint vaoID = model.getVaoId();
			shader.use();
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(1.0f, 1.0f, 1.0f, alpha);
			bindVAO(vaoID);
			glEnableVertexAttribArray(0); // Position
			glEnableVertexAttribArray(1); // Texture
			glEnableVertexAttribArray(2); // Normal
			glm::mat4 transformationMatrix = Maths::createTransformationMatrix(entity.position, entity.rotX, entity.rotY, entity.rotZ, entity.scale);
			shader.loadTransformationMatrix(transformationMatrix);
			shader.loadAlpha(alpha);
			//shader.loadProjectionMatrix(projectionMatrix);

			//glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount()); // This draws from vertices
			glActiveTexture(GL_TEXTURE0); // sampler2D thingy
			glBindTexture(GL_TEXTURE_2D, texture.getId());
			glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0); // This draws using our bound indices array
			//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glDisableVertexAttribArray(2);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(0);
			unBindVAO();
			if (alpha != 1.0f)
			{
				glDisable(GL_BLEND);
				glDisable(GL_CULL_FACE);
			}
			shader.unUse();
		}
};