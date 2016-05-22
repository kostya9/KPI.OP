#include "Shadow.h"

Shadow::Shadow(Loader * loader, glm::fvec3 position)
{
	vector<TexturedModel> models = loader->objToModel("../opengllearn/models/playerBall/playerBall.obj");

	for (TexturedModel model : models)
		entities.push_back(Entity(model));
	for (Entity & en : entities)
		en.alpha = 0.4f;
	this->alpha = 0.4f;
	precision = 0.5f;
}

void Shadow::queuePosition(glm::fvec3 pos)
{
	positions.push(pos);
}

void Shadow::update()
{
	setPosition(positions.front());
	positions.pop();
}
