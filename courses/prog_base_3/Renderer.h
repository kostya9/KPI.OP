#pragma once
#include "MainHeaders.h"
class Renderer
{
	public:
		void prepare()
		{
			glfwPollEvents();
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

		}
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