#include "Wall.h"
#include "WallHole.h"
#include <glm/gtx/norm.hpp>

Wall::Wall(Loader * loader, glm::vec3 position)
{
	static vector<TexturedModel> models = loader->objToModel("../opengllearn/models/wall/wall_upd.obj");
	static vector<TexturedModel> modelsHole = loader->objToModel("../opengllearn/models/wall/cylinderAsHole.obj");
	vector<Entity> entitiesHole;

	for (TexturedModel model : models)
		entities.push_back(Entity(model));

	for (TexturedModel model : modelsHole)
		entitiesHole.push_back(Entity(model));

	this->hole = new WallHole(entitiesHole, position);
	this->setPosition(position);
	this->hole->hideObject();
}

void Wall::render(MasterRenderer * renderer)
{
	GameObject::render(renderer);
	hole->render(renderer);
}

void Wall::render(MasterRenderer * renderer, glm::fvec3 object, GLfloat distance)
{
	GameObject::render(renderer, object, distance);
	hole->render(renderer, object, distance);
}

void Wall::setPosition(glm::fvec3 position)
{
	GameObject::setPosition(position);
	hole->setPosition(position);
}

void Wall::setAlpha(GLfloat alpha)
{
	GameObject::setAlpha(alpha);
	hole->setAlpha(alpha);
}

bool Wall::hasHole()
{
	return hole->getVisibility();
}

WallHole::HOLE_DIRECTION Wall::getHoleDirection()
{
	return hole->getDirection();
}

void Wall::showHole(WallHole::HOLE_DIRECTION direction)
{
	if (hole->makeVisible(direction) == WallHole::VISIBILITY_ROTATION_CHANGED)
		this->rotate(glm::vec3(0.0f, 90.0f, 0.0f));
}

void Wall::hideHole()
{
	hole->makeInvisible();
}

Wall::~Wall()
{
	delete hole;
}

Wall::COLLISION_STATUS Wall::isMovementColliding(glm::fvec3 positionFrom, glm::fvec3 positionDest)
{
	GLfloat distanceToWall = glm::length2(this->getPosition() - positionDest);

	if (distanceToWall > 0.3)
		return COLLISION_FALSE;

	if (hole->getVisibility() == false)
		return COLLISION_TRUE;

	glm::fvec3 movement = glm::abs(positionDest - positionFrom);

	if (this->getHoleDirection() == WallHole::HOLE_DIRECTION_X)
	{
		if (movement.x > 0.5)
			return COLLISION_HOLE;
	}
	else // z
	{
		if (movement.z > 0.5)
			return COLLISION_HOLE;
	}
	return COLLISION_TRUE;
}