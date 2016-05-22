#pragma once
#include "MainHeaders.h"
class Model
{
	private:
		GLuint vaoID;
		GLuint vertexCount;
	public:
		Model() {};// copy requires default constructor for some reason
		/*Creates a model from a VAO(Vertex Array Object) linked to it and count of it's vertices*/
		Model(GLuint vaoID, GLuint vertexCount)
		{
			this->vertexCount = vertexCount;
			this->vaoID = vaoID;
		}
		/*Gets the VAO linked to this model*/
		GLuint getVaoId() const
		{
			return vaoID;
		}
		/*Gets the vertex coutn of this model*/
		GLuint getVertexCount()
		{
			return vertexCount;
		}
};