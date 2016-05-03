#include "MenuOptionButton.h"

MenuOptionButton::MenuOptionButton(Loader * loader, Font * font, glm::fvec3 color, string text) : MenuOption(font, vector<Entity>(), color, text)
{
	vector<TexturedModel> models = loader->objToModel("models/menu/button/button.obj");
	for (TexturedModel m : models)
		entities.push_back(Entity(m, glm::fvec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 1.0f));
}