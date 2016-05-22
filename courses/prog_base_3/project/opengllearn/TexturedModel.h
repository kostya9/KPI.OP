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
		Model getModel() const
		{
			return model;
		}
		Texture getTexture() const
		{
			return texture;
		}
		int operator==(const TexturedModel& other) const
		{
			return (this->model.getVaoId() == other.getModel().getVaoId()) && (this->texture.getId() == other.getTexture().getId());
		}
};

namespace std
{
	template <>
	struct hash<TexturedModel>
	{
		size_t operator()(TexturedModel const & x) const noexcept
		{
			return (
				(51 + std::hash<int>()(x.getModel().getVaoId())) * 51
				+ std::hash<int>()(x.getTexture().getId())
				);
		}
	};
}