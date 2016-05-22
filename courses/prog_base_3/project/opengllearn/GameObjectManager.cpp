#include "GameObjectManager.h"
GameObjectManager::GameObjectManager()
{
	renderer = new MasterRenderer();
}
void GameObjectManager::shake(GLfloat time)
{
	this->renderer->shake(time);
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
	/*shader->use();


	shader->unUse();
	renderer->prepare();*/

	shadow->queuePosition(player->getPosition());
	shadow->hideObject();
	if ((glfwGetTime() - shadowTimeCreated) > 3.f)
	{
		shadow->showObject();
		shadow->update();
	}
	shadow->render(renderer);
	player->render(renderer);
	if (menu != nullptr)
		menu->render(renderer);
	if(hole != nullptr)
		hole->render(renderer, player->getPosition(), 70.0f);
	field->render(renderer, player->getPosition(), 70.0f);
	for (GameObject * obj : objects)
		obj->render(renderer, player->getPosition(), 70.0f);
	for (Wall * obj : walls)
	{
		obj->render(renderer, player->getPosition(), 70.0f);
	}

	if (menu == nullptr)
	{
		renderer->render(light, (player->getCamera()));
		renderer->cleanUp();
	}
	else
	{
		renderer->render((menu->getLight()), (menu->getCamera()));
		renderer->cleanUp();
	}
	renderer->update();
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

void GameObjectManager::addObject(Shadow * shadow)
{
	shadowTimeCreated = glfwGetTime();
	this->shadow = shadow;
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

void GameObjectManager::addObject(Menu * menu)
{
	this->menu = menu;
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

Shadow * GameObjectManager::getShadow()
{
	return shadow;
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
	if(hole != nullptr)
		delete hole;
	delete light;
	//if (menu != nullptr)
		//delete menu;
	delete renderer;
	delete player;
}
