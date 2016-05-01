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
	cam->pitch(M_PI / 4);
}
GLfloat Player::getEnergy()
{
	return energy;
}
void Player::render(Renderer * renderer, StaticShader shader)
{
	glm::vec3 prevPos = this->position;
	this->setScale(energy);
	setSineHeightPosition();
	GameObject::render(renderer, shader);
	this->setPosition(prevPos);
}
void Player::startDamaging(GLuint dmgPerSecond)
{
	this->dmgPerSecond = dmgPerSecond;
}
void Player::stopDamaging()
{
	this->dmgPerSecond = 0;
}
void Player::addDamage(GLfloat dmg)
{
	const GLfloat i = 300.f;
	energy -= (dmg / (dmg + i));
}
bool Player::canBurnWall()
{
	return getEnergy() > 0.8f;
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
	addDamage(dmgPerSecond * Window::getDeltaTime());
	if (this->energy < 1.0f)
	{
		this->energy += 0.001f;
	}
	if (moveState != MOVE_NO)
	{
		glm::fvec3 movement = getMovementVector();
		glm::fvec3 camPosition = cam->getPosition();
		this->position += movement * Window::getDeltaTime();
		this->cam->setPosition(camPosition + movement * Window::getDeltaTime());
		this->position.y = height;
	}
}
glm::fvec3 Player::getMovementVector()
{
	GLfloat precision = 0.001f;
	GLfloat deltaDistance = glm::length2(this->dest - this->position);
	if (deltaDistance < precision)
	{
		this->position = this->dest;
		stopDamaging();
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
void Player::setSineHeightPosition()
{
	GLfloat dy = 0.2f * glm::sin(glfwGetTime());
	this->setPosition(glm::vec3(position.x, position.y + dy, position.z));
}