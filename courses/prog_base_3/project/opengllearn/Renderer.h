#pragma once
#include "MainHeaders.h"
#include "StaticShader.h"
#include "TexturedModel.h"
#include "Model.h"
#include "Entity.h"
class Renderer
{
	public:
		/*Prepares the window for drawing the next frame*/
		void prepare()
		{
			glfwPollEvents();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // RED 
		}
		/*Renders(draws) a model to the screen*/
		void render(Entity entity, StaticShader shader)
		{
			TexturedModel texturedModel = entity.model;
			Model model = texturedModel.getModel();
			Texture texture = texturedModel.getTexture();
			GLuint vaoID = model.getVaoId();
			shader.use();
			bindVAO(vaoID);
			glEnableVertexAttribArray(0); // Position
			glEnableVertexAttribArray(1); // Texture
			glm::mat4 transformationMatrix = Maths::createTransformationMatrix(entity.position, entity.rotX, entity.rotY, entity.rotZ, entity.scale);
			shader.loadTransformationMatrix(transformationMatrix);

			//glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount()); // This draws from vertices
			glActiveTexture(GL_TEXTURE0); // sampler2D thingy
			glBindTexture(GL_TEXTURE_2D, texture.getId());
			glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0); // This draws using our bound indices array
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(0);
			unBindVAO();
			shader.unUse();
		}
};