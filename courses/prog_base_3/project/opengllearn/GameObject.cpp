#include "GameObject.h"

GameObject::GameObject(vector<Entity> entities, glm::fvec3 position)
{
	objects.push_back(this);
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

void GameObject::scale(GLfloat times)
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

void GameObject::render(Renderer * renderer, StaticShader shader)
{
	if(show)
		for (Entity en : entities)
		{
			renderer->render(en, shader, alpha/**/);
		}
}

vector<GameObject*> GameObject::getObjects()
{
	return objects;
}

GameObject::~GameObject()
{
	int i = 0;
	for (GameObject * object : objects)
	{
		if (object == this)
		{
			objects.erase(objects.begin() + i);
			break;
		}
		i++;
	}
}
