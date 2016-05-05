#include "GameObject.h"

GameObject::GameObject(vector<Entity> entities, glm::fvec3 position)
{
	this->entities = entities;
	this->setPosition(position);
	this->show = true;
}

GameObject::GameObject()
{
	position = glm::vec3();
	this->show = true;
}

void GameObject::hideObject()
{
	this->show = false;
}

void GameObject::showObject()
{
	this->show = true;
}

void GameObject::rotate(glm::fvec3 rotation)
{
	for (Entity & e : entities)
	{
		e.increaseRotation(rotation.x, rotation.y, rotation.z);
	}
}

void GameObject::setScale(GLfloat times)
{
	for (Entity & e : entities)
	{
		e.scale = times;
	}
}

void GameObject::setPosition(glm::fvec3 position)
{
	this->position = position;
	for (Entity & e : entities)
	{
		e.position = position;
	}
}

bool GameObject::getVisibility()
{
	return show;
}

void GameObject::setAlpha(GLfloat alpha)
{
	this->alpha = alpha;
}

bool GameObject::isAtPositionNeighborhood(glm::fvec3 position)
{
	position.y = 0.5f;
	GLfloat deltaDistance = glm::length2(position - this->position);
	if (deltaDistance < precision)
		return true;
	else
		return false;
}

void GameObject::render(Renderer * renderer, StaticShader shader)
{
	if(show)
		for (Entity en : entities)
		{
			renderer->render(en, shader, alpha/**/);
		}
}

GameObject::~GameObject()
{
}
