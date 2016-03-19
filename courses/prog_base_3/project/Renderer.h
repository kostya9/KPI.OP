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
			glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());
			glDisableVertexAttribArray(0);
			unBindVAO();
		}
};