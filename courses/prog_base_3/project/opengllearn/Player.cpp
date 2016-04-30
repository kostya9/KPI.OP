#include "Player.h"
#include "math.h"
#include <glm/gtx/norm.hpp>
#include <windows.h>
Player::Player(Loader * loader, glm::fvec3 position, Camera * c) : GameObject(entities, position)
{
	vector<TexturedModel> models = loader->objToModel("../opengllearn/models/playerBall/playerBall.obj");

	for (TexturedModel model : models)
		entities.push_back(Entity(model));
	energy = 1.0f;
	float delta = 3.0f;
	moveState = MOVE_NO;
	dest = glm::vec3(0.0f, 0.0f, 0.0f);
	this->cam = c;
	cam->setPosition(position);
	cam->moveForward(-delta);
	cam->moveUp(delta);
	// DEBUG
	//cam.yaw(M_PI / 2);
	//cam.moveLeft(3.0f);
	//cam.moveForward(-3.0f);

	cam->pitch(M_PI / 4);
}
void Player::render(Renderer * renderer, StaticShader shader)
{
	glm::vec3 prevPos = this->position;
	setSineHeightPosition();
	GameObject::render(renderer, shader);
	this->setPosition(prevPos);
}
bool Player::isMoving()
{
	if (moveState == MOVE_NO)
		return false;
	else
		return true;
}
void Player::moveLeft()
{
	moveLeft(1);
}
void Player::moveRight()
{
	moveRight(1);
}
void Player::moveForward()
{
	moveForward(1);
}
void Player::moveBackwards()
{
	moveBackwards(1);
}
void Player::moveLeft(GLint times)
{
	if (this->moveState == MOVE_NO)
	{
		this->moveState = MOVE_LEFT;
		this->dest = this->position + glm::fvec3(-times * 1.0f, 0.0f, 0.0f);
	}
}
void Player::moveRight(GLint times)
{
	if (this->moveState == MOVE_NO)
	{
		this->moveState = MOVE_RIGHT;
		this->dest = this->position + glm::fvec3(times * 1.0f, 0.0f, 0.0f);
	}
}
void Player::moveForward(GLint times)
{
	if (this->moveState == MOVE_NO)
	{
		this->moveState = MOVE_FORWARD;
		this->dest = this->position + glm::fvec3(0.0f, 0.0f, times * -1.0f);
	}
}
void Player::moveBackwards(GLint times)
{
	if (this->moveState == MOVE_NO)
	{
		this->moveState = MOVE_BACKWARD;
		this->dest = this->position + glm::fvec3(0.0f, 0.0f, times * 1.0f);
	}
}
void Player::update()
{
	if (moveState != MOVE_NO)
	{
		glm::fvec3 movement = getMovementVector();
		this->position += movement * Window::getDeltaTime();
		this->position.y = height;
	}
}
glm::fvec3 Player::getMovementVector()
{
	GLfloat precision = 0.001;
	GLfloat deltaDistance = glm::length2(this->dest - this->position);
	if (deltaDistance < precision)
	{
		this->position = this->dest;
		this->moveState = MOVE_NO;
		return glm::fvec3();
	}
	glm::fvec3 movement = glm::fvec3();
	switch (moveState)
	{
		case MOVE_FORWARD:
			movement.z = -1.0f;
		break;
		case MOVE_BACKWARD:
			movement.z = 1.0f;
		break;
		case MOVE_LEFT:
			movement.x = -1.0f;
		break;
		case MOVE_RIGHT:
			movement.x = 1.0f;
		break;
	}
	movement.y = 0.0f;
	return movement;
}
Camera * Player::getCamera()
{
	return cam;
}
/*
Player::PLAYER_MOVE_STATUS Player::move(GameObjectManager * manager)
{
	static Wall * wall = nullptr;
	if (moveState == MOVE_NO)
	{
		moveState = getMovementStateFromInputKeys();
		if (moveState == MOVE_NO)
			return NO_COMMANDS;

		Wall::COLLISION_STATUS status = getColliderIfAHole(manager, &wall);
		if (status == Wall::COLLISION_HOLE)
		{
			wall->setAlpha(0.5f);
			return COLLISION_UNDETECTED;
		}
		if (status == Wall::COLLISION_TRUE)
			return COLLISION_DETECTED;
	}
	moveModel(wall);
	return COLLISION_UNDETECTED;
}

void Player::moveModel(Wall * wall)
{
	glm::fvec3 movement = Player::getMovementVector();
	movement *= Window::getDeltaTime();
	this->cam->setPosition(this->cam->getPosition() + movement);		 // Camera managing here
	for (Entity & e : entities)
	{
		this->position += movement;
		if (moveState == MOVE_NO)
		{
			if(wall != nullptr)
				wall->setAlpha(1.0f);
			this->setPosition(dest);
			return;
		}
		e.increasePosition(movement);
	}
}
*/
void Player::setSineHeightPosition()
{
	GLfloat dy = 0.2 * glm::sin(glfwGetTime());
	this->setPosition(glm::vec3(position.x, position.y + dy, position.z));
}
/*
Wall::COLLISION_STATUS Player::getColliderIfAHole(GameObjectManager * manager, Wall ** wall_out)
{
	if (manager != nullptr)
	{
		Wall * wall;
		Wall::COLLISION_STATUS status = manager->isMovementColliding(this->position, dest, &wall);
		if (status == Wall::COLLISION_TRUE)
		{
			moveState = MOVE_NO;
			*wall_out = nullptr;
			return status;
		}
		else if (status == Wall::COLLISION_HOLE)
		{
			dest += (dest - this->position);
			dest.x = glm::round(dest.x);
			dest.z = glm::round(dest.z);
			*wall_out = wall;
			return status;
		}
		else
			return status;
	}
}*/