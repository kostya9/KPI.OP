#include "GuiRenderer.h"
GuiRenderer::GuiRenderer(Loader * loader)
{
	GLfloat positions[] = { -1.f, 1.f, -1.f, -1.f, 1.f, 1.f, 1.f, -1.f };
	quad = loader->loadToVao(positions, 8);
	shader = GuiShader();
}

GLuint GuiRenderer::getIdOnMousePosition(vector<MenuOption *> options)
{
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glClearColor(1.f, 1.f, 1.f, 1.f);
	picker.use();
	glBindVertexArray(quad.getVaoId());
	glEnableVertexAttribArray(0);
	for (MenuOption * option : options)
	{
		GuiTexture gui = option->getTexture();
		glm::mat4 matrix = Maths::createTransformationMatrix(gui.getPosition(), gui.getScale());
		picker.loadTransformation(matrix);
		GLchar id = option->getID();
		int r = (id & 0x000000FF) >> 0;
		int g = (id & 0x0000FF00) >> 8;
		int b = (id & 0x00FF0000) >> 16;
		glm::fvec3 color = glm::fvec3(r/255.f, g/255.f, b/255.f);
		picker.loadPickerColor(color);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, quad.getVertexCount());
	}
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	picker.unUse();
	GLdouble xPos, yPos;
	glfwGetCursorPos(Window::getGLFWWindow(), &xPos, &yPos);
	GLubyte color[3];
	glFlush();
	glFinish();
	glReadPixels((int)xPos, Window::getHeight() - (int)yPos, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, color);
	printf("Real\tR: %d\tG: %d\tB: %d\n", color[0], color[1], color[2]);
	int pickedID =
		color[0] +
		color[1] * 256 +
		color[2] * 256 * 256;
	printf("pickedID - %d\n", pickedID);
	return pickedID;

	
}

void GuiRenderer::render(vector<GuiTexture> textures)
{
	shader.use();
	glBindVertexArray(quad.getVaoId());
	glEnableVertexAttribArray(0);
	for (GuiTexture gui : textures)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, gui.getTexture());
		glm::mat4 matrix = Maths::createTransformationMatrix(gui.getPosition(), gui.getScale());
		shader.loadTransformation(matrix);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, quad.getVertexCount());
	}
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader.unUse();
}
