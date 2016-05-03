#include "GameObjectManager.h"
GameObjectManager::GameObjectManager()
{
	shader = new StaticShader();
	renderer = new Renderer(*shader);
}
Wall::COLLISION_STATUS GameObjectManager::isMovementColliding(glm::fvec3 positionFrom, glm::fvec3 positionDest, Wall ** collider)
{
	for (Wall * wall : walls)
	{
		Wall::COLLISION_STATUS status = wall->isMovementColliding(positionFrom, positionDest);
		if (status != Wall::COLLISION_FALSE)
		{
			if(collider != nullptr)
				*collider = wall;
			return status;
		}
	}
	if (collider != nullptr)
		*collider = nullptr;
	return Wall::COLLISION_FALSE;
}

void GameObjectManager::renderAll()
{
	shader->use();
	shader->loadViewMatrix(*(player->getCamera()));
	shader->loadLight(*light);
	shader->unUse();
	renderer->prepare();
	player->render(renderer, *shader);
	hole->render(renderer, *shader);
	field->render(renderer, *shader);
	for (GameObject * obj : objects)
		obj->render(renderer, *shader);
	for (Wall * obj : walls)
		obj->render(renderer, *shader);
}

void GameObjectManager::addObject(Wall * wall)
{
	walls.push_back(wall);
}

void GameObjectManager::addObject(Player * player)
{
	this->player = player;
}

void GameObjectManager::addObject(Field * field)
{
	this->field = field;
}

void GameObjectManager::addObject(GameObject * object)
{
	objects.push_back(object);
}

void GameObjectManager::addObject(Light * light)
{
	this->light = light;
}

void GameObjectManager::addObject(WhiteHole * hole)
{
	this->hole = hole;
}

WhiteHole * GameObjectManager::getWhiteHole()
{
	return this->hole;
}

Field * GameObjectManager::getField()
{
	return field;
}

Light * GameObjectManager::getLight()
{
	return light;
}

Player * GameObjectManager::getPlayer()
{
	return player;
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
	delete renderer;
	shader->deleteShader();
	delete shader;
	delete player;
}
