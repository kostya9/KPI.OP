#include "Loader.h"

Model Loader::loadToVao(GLfloat positions[],  GLuint size_pos, GLuint indices[], GLuint size_ind, GLfloat textureCoorinates[], GLuint size_tex)
{
	GLuint vaoID = createVAO();
	bindVAO(vaoID);
	bindIndicesBuffer(indices, size_ind);
	dataToAttributes(0, 3, positions, size_pos);
	dataToAttributes(1, 2, textureCoorinates, size_tex);
	unBindVAO();
	return Model(vaoID, size_ind);
}

GLuint Loader::loadTexture(GLchar * path)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object		
											 // Set the texture wrapping parameters
	textures.push_back(textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load image
	int width, height;
	unsigned char * img = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
	//Binding the image to the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(img);
	glBindTexture(GL_TEXTURE_2D, 0);
	return textureID;
}

GLuint Loader::createVAO()
{
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	vaos.push_back(vaoID);
	return vaoID;
}

void Loader::dataToAttributes(GLint attribNum, GLuint coordinateSize, GLfloat data[], GLuint size)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	vbos.push_back(vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), data, GL_STATIC_DRAW);
	glVertexAttribPointer(attribNum, coordinateSize, GL_FLOAT, GL_FALSE, coordinateSize * sizeof(GLfloat), (GLvoid*)0);
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
	for (GLuint v : textures)
		glDeleteTextures(1, &v);
}
