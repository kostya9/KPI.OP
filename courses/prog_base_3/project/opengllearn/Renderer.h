#pragma once
#include <algorithm>
#include <vector>
#include <unordered_map>
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
	const GLfloat FAR_PLANE = 1000.0f;// WTF>????????????
	GLfloat time = 0;
	glm::fmat4 projectionMatrix;
	StaticShader shader;
	void createProjectionMatrix()
	{
		projectionMatrix = glm::perspective(FOV, 1.0f, NEAR_PLANE, FAR_PLANE);
		//projectionMatrix = glm::ortho(0.0f, /*(float)Window::getWidth()/100/**/ 10.0f, 0.0f,/*(float)Window::getHeight()/100, 0.0f/**/4.0f, 0.1f, 100.0f/*, NEAR_PLANE, FAR_PLANE*/);
	}
	public:
		Renderer(StaticShader shader)
		{
			this->shader = shader;
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
			glClearColor(64/255.0f, 64 / 255.0f, 64 / 255.0f, 1.0f); // Dark Grey
		}
		/*Renders(draws) a model to the screen*/
		void shake(StaticShader shader, GLfloat time)
		{
			shader.use();
			this->time = time;
			shader.loadShake(GL_TRUE, time);
			shader.unUse();
		}
		void unShake(StaticShader shader)
		{
			shader.use();
			this->time = 0;
			shader.loadShake(GL_FALSE, 0);
			shader.unUse();
		}
		void update(StaticShader shader)
		{
			if (this->time < 0)
			{
				unShake(shader);
			}
			else if (this->time > 0)
			{
				this->time -= 5 * Window::getDeltaTime();
				shake(shader, time);
			}
		}
		void render(unordered_map<TexturedModel, vector<Entity> *> entities)
		{
			glEnable(GL_CULL_FACE);
			for (pair<TexturedModel, vector<Entity> *> p : entities)
			{
				TexturedModel model = p.first;
				prepareTexturedModel(model);
				vector<Entity> * ents = p.second;
				for (Entity entity : *ents)
				{
					if (entity.alpha != 1.0f)
					{
						glEnable(GL_BLEND);
						glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					}
					prepareInstance(entity);
					glDrawElements(GL_TRIANGLES, model.getModel().getVertexCount(), GL_UNSIGNED_INT, 0); // This draws using our bound indices array
					if (entity.alpha != 1.0f)
					{
						glDisable(GL_BLEND);
					}
				}
				unbindTexturedModel();
			}
		}

		void prepareTexturedModel(TexturedModel text_model)
		{
			Model model = text_model.getModel();
			Texture texture = text_model.getTexture();
			GLuint vaoID = model.getVaoId();
			shader.use();
			bindVAO(vaoID);
			glActiveTexture(GL_TEXTURE0); // sampler2D thingy
			glBindTexture(GL_TEXTURE_2D, text_model.getTexture().getId());
			glEnableVertexAttribArray(0); // Position
			glEnableVertexAttribArray(1); // Texture
			glEnableVertexAttribArray(2); // Normal
		}
		void unbindTexturedModel()
		{
			glDisableVertexAttribArray(2);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(0);
			unBindVAO();
			shader.unUse();
		}
		void prepareInstance(Entity entity)
		{
			shader.use();
			glm::mat4 transformationMatrix = Maths::createTransformationMatrix(entity.position, entity.rotX, entity.rotY, entity.rotZ, entity.scale);
			shader.loadTransformationMatrix(transformationMatrix);
			glColor4f(1.0f, 1.0f, 1.0f, entity.alpha);
			shader.loadAlpha(entity.alpha);
			//shader.loadProjectionMatrix(projectionMatrix);
		}
};