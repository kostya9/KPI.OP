#include "Loader.h"

Model Loader::loadToVao(GLfloat positions[],  GLuint size)
{
	GLuint vaoID = createVAO();
	bindVAO(vaoID);
	dataToVBO(0, positions, size);
	unBindVAO();
	return Model(vaoID, size/3);
}

GLuint Loader::createVAO()
{
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	vaos.push_back(vaoID);
	return vaoID;
}

void Loader::dataToVBO(GLint attribNum, GLfloat data[], GLuint size)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	vbos.push_back(vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), data, GL_STATIC_DRAW);
	glVertexAttribPointer(attribNum, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::releaseVOs()
{
	for(GLuint v : vaos)
		glDeleteVertexArrays(1, &v);
	for(GLuint v : vbos)
		glDeleteBuffers(1, &v);
}
