#pragma once
#include "MainHeaders.h"

class Loader {
	public:
		/*Creates a Model from Vertex array*/
		Model loadToVao(GLfloat positions[], GLuint size);
		/*Cleans VAOs and VBOs, created at dataToVbo and createVAO */
		void releaseVOs();
	private:
		std::vector<GLuint> vaos;
		std::vector<GLuint> vbos;
		GLuint createVAO();
		void dataToVBO(GLint attribNum, GLfloat data[], GLuint size);
};	