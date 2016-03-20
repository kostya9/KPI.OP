#pragma once
#include "MainHeaders.h"
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
		void render(Model model)
		{
			GLuint vaoID = model.getVaoId();
			bindVAO(vaoID);
			glEnableVertexAttribArray(0);
			//glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount()); // This draws from vertices
			glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0); // This draws using our bound indices array
			glDisableVertexAttribArray(0);
			unBindVAO();
		}
};