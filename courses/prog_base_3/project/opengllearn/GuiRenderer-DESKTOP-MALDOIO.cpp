#include "GuiRenderer.h"

GuiRenderer::GuiRenderer(Loader * loader)
{
	GLfloat positions[] = { -1.f, 1.f, -1.f, -1.f, 1.f, 1.f, 1.f, -1.f };
	quad = loader->loadToVao(positions, 4);
	shader = GuiShader();
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
