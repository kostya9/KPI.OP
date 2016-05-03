#include "WhiteHole.h"

WhiteHole::WhiteHole(glm::fvec3 position,Loader * loader)
{
	vector<TexturedModel> models = loader->objToModel(string("models/whiteHole/whiteHole.obj"));

	for (TexturedModel m : models)
	{
		this->entities.push_back(Entity(m, position, 0.0f, 0.0f, 0.0f, 1.0f));
	}
	this->setPosition(position);
	this->showObject();
}
