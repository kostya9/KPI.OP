#pragma once
#include "MainHeaders.h"
#include "Texture.h"
#include "Renderer.h"
#include "Shader.h"
#include <map>
class Font
{
	private:
		struct Character
		{
			Texture text;
			glm::ivec2 size; // the size of a char
			glm::ivec2 bearing; // offset to top
			GLuint advance; // offset to the right
		};
		GLuint VAO, VBO;
		const GLchar * fragPath = "shaders/fonts/fragment.sh";
		const GLchar * vertPath = "shaders/fonts/vertex.sh";
		Shader shader;
		map<GLchar, Character> chars;
	public:
		Font(GLchar * fileName);
		void renderText(GLchar * text, glm::fvec2 position, glm::fvec3 color, GLfloat scale);
};