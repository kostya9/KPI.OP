#include "GameObjectManager.h"
Wall::COLLISION_STATUS GameObjectManager::isMovementColliding(glm::fvec3 positionFrom, glm::fvec3 positionDest)
{

	for (Wall * wall : walls)
	{
		Wall::COLLISION_STATUS status = wall->isMovementColliding(positionFrom, positionDest);
		if (status != Wall::COLLISION_FALSE)
			return status;
	}
	return Wall::COLLISION_FALSE;
}

void GameObjectManager::renderAll(Renderer * renderer, StaticShader shader)
{
	for (GameObject * obj : objects)
		obj->render(renderer, shader);
	for (Wall * obj : walls)
		obj->render(renderer, shader);
}

void GameObjectManager::addObject(Wall * wall)
{
	walls.push_back(wall);
}

void GameObjectManager::addObject(GameObject * object)
{
	objects.push_back(object);
}

void GameObjectManager::deleteObject(GameObject * object)
{
	int i = 0;
	for (GameObject * go : objects)
	{
		if (object == go)
		{
			objects.erase(objects.begin() + i);
			return;
		}
		i++;
	}
}

GameObjectManager::~GameObjectManager()
{
	for (GameObject * obj : objects)
		delete obj;
	for (Wall * obj : walls)
		delete obj;
}
