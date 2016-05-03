#include "MenuOptionSlider.h"

MenuOptionSlider::MenuOptionSlider(Loader * loader, Font * font, glm::fvec3 color) : MenuOption(font, vector<Entity>(), color, string(""))
{
	vector<TexturedModel> models = loader->objToModel("models/menu/slider/slider.obj");
	for (TexturedModel m : models)
		entities.push_back(Entity(m, glm::fvec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 1.0f));
	for (Entity & e : entities)
		e.scale = 0.1f;
	this->scale = 0.1f;
}