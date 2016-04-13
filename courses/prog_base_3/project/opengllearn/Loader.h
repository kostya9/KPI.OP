#pragma once
#include "Model.h"
#include "MainHeaders.h"
#include "TexturedModel.h"
using namespace std;
class Loader {
	public:
		/*Creates a Model and binds it ti Vertex Array Object(VAO)*/
		/*WARNING Texture coordinate system origin(0, 0) is at TOP LEFT*/
		Model loadToVao(GLfloat positions[], GLuint size_pos, GLuint indices[], GLuint size_ind, 
						GLfloat textureCoorinates[], GLuint size_tex, GLfloat normals[], GLuint size_normals);
		GLuint loadTexture(GLchar * path);
		vector<TexturedModel> objToModel(string path);
		/*Cleans VAOs and VBOs, created at dataToVbo and createVAO */
		void  releaseVOs();
	private:
		std::vector<GLuint> vaos;
		std::vector<GLuint> vbos;
		std::vector<GLuint> textures;
		GLuint createVAO();
		/*Binds some data to attributes of an VAO*/
		void dataToAttributes(GLint attribNum, GLuint coordinateSize, GLfloat data[], GLuint size);
		/*Storing vertices using indices*/
		void bindIndicesBuffer(GLuint indices[], GLuint size);
};	