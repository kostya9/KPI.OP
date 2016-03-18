#pragma once
class Model
{
	private:
		GLuint vaoID;
		GLuint vertexCount;
	public:
		Model(GLuint vaoID, GLuint vertexCount)
		{
			this->vertexCount = vertexCount;
			this->vaoID = vaoID;
		}
		GLuint getVaoId()
		{
			return vaoID;
		}
		GLuint getVertexCount()
		{
			return vertexCount;
		}
};