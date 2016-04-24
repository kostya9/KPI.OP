#include "Wall.h"

Wall::Wall(Loader * loader, glm::vec3 position)
{
	vector<TexturedModel> models = loader->objToModel("../opengllearn/models/wall/wallWIthHole.obj");
	vector<TexturedModel> modelsHole = loader->objToModel("../opengllearn/models/wall/cylinderAsHole.obj");

	for (TexturedModel model : models)
		entities.push_back(Entity(model));

	for (TexturedModel model : modelsHole)
		entitiesHole.push_back(Entity(model));
	this->setPosition(position);
	holeVisible = true;
}

void Wall::render(Renderer * renderer, StaticShader shader)
{
	GameObject::render(renderer, shader);
	if (holeVisible == false)
	{
		for (Entity entity : entitiesHole)
			renderer->render(entity, shader);
	}
}

void Wall::setPosition(glm::fvec3 position)
{
	GameObject::setPosition(position);
	for (Entity & e : entitiesHole)
	{
		e.position = position;
	}
}

void Wall::showHole()
{
	holeVisible = true;
}

void Wall::hideHole()
{
	holeVisible = false;
}
