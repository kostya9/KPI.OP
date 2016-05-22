#pragma once
#include "MainHeaders.h"
class Texture
{
	public:
		Texture() {};// copy requires default constructor for some reason
		Texture(int textureID)
		{
			this->textureID = textureID;
		}
		GLuint getId() const
		{
			return textureID;
		}
	private:
		int textureID;
};