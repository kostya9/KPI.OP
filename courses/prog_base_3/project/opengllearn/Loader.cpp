#include "Loader.h"

Model Loader::loadToVao(GLfloat positions[],  GLuint size_pos, GLuint indices[], GLuint size_ind)
{
	GLuint vaoID = createVAO();
	bindVAO(vaoID);
	bindIndicesBuffer(indices, size_ind);
	dataToAttributes(0, positions, size_pos);
	unBindVAO();
	return Model(vaoID, size_ind);
}

GLuint Loader::createVAO()
{
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	vaos.push_back(vaoID);
	return vaoID;
}

void Loader::dataToAttributes(GLint attribNum, GLfloat data[], GLuint size)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	vbos.push_back(vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), data, GL_STATIC_DRAW);
	glVertexAttribPointer(attribNum, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::bindIndicesBuffer(GLuint indices[], GLuint size)
{
	GLuint eboID;
	glGenBuffers(1, &eboID);
	vbos.push_back(eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * size, indices, GL_STATIC_DRAW);// TODO should we unbind?
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Why shouldn't we do this?
}

void Loader::releaseVOs()
{
	for(GLuint v : vaos)
		glDeleteVertexArrays(1, &v);
	for(GLuint v : vbos)
		glDeleteBuffers(1, &v);
}
