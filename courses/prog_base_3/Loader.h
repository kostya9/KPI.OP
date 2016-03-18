#pragma once
#include "MainHeaders.h"

class Loader {
	public:
		Model loadToVao(GLfloat positions[], GLuint size);
		void releaseVOs();
	private:
		std::vector<GLuint> vaos;
		std::vector<GLuint> vbos;
		GLuint createVAO();
		void dataToVBO(GLint attribNum, GLfloat data[], GLuint size);
};	