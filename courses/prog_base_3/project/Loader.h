#pragma once
#include "Model.h"
#include "MainHeaders.h"

class Loader {
	public:
		/*Creates a Model from Vertex array*/
		Model loadToVao(GLfloat positions[], GLuint size_pos, GLuint indices[], GLuint size_ind);
		/*Cleans VAOs and VBOs, created at dataToVbo and createVAO */
		void releaseVOs();
	private:
		std::vector<GLuint> vaos;
		std::vector<GLuint> vbos;
		GLuint createVAO();
		/*Storing vertices*/
		void dataToAttributes(GLint attribNum, GLfloat data[], GLuint size);
		/*Storing vertices using indices*/
		void bindIndicesBuffer(GLuint indices[], GLuint size);
};	