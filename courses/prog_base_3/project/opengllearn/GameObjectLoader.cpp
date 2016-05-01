#include "GameObjectLoader.h"

GameObjectLoader::GameObjectLoader(GameObjectManager * manager)
{
	this->loader = new Loader(); // temp
	this->manager = manager;

}

void GameObjectLoader::generateField(glm::fvec2 center, GLuint size)
{
	Field * field = new Field(loader, size, glm::vec3(center.x, 0.0f, center.y));
	manager->addObject(field);
}

void GameObjectLoader::createPlayer(glm::fvec2 position)
{
	Camera * camera = new Camera();
	Player * player = new Player(loader, glm::vec3(0.0f, 0.5f, 1.0f), camera);
	manager->addObject(player);
}

void GameObjectLoader::createWall(glm::fvec2 position)
{
	Wall * wall = new Wall(loader, glm::vec3(position.x, 0.01f, position.y));
	//wall->showHole(WallHole::HOLE_DIRECTION_X);
	//wall->hideHole();
	manager->addObject(wall);
}

void GameObjectLoader::createLight(GLfloat brightness, glm::fvec3 position)
{
	Light * light = new Light(position, glm::vec3(brightness, brightness, brightness));
	manager->addObject(light);
}

GameObjectLoader::~GameObjectLoader()
{
	loader->releaseVOs();
	delete loader;
}
