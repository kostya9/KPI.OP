#pragma once
#include "Texture.h"
#include "Model.h"
#include "MainHeaders.h"
class TexturedModel
{
	private:
		Model model;
		Texture texture;
	public:
		TexturedModel() {}
		TexturedModel(Model model, Texture texture)
		{
			this->model = model; // requires default constructor for some reason
			this->texture = texture;
		}
		Model getModel()
		{
			return model;
		}
		Texture getTexture()
		{
			return texture;
		}
};