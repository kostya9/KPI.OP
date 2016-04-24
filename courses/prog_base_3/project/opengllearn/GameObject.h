#pragma once
#include "MainHeaders.h"
#include "Renderer.h"
#include "Entity.h"
#include "Shader.h"
// TODO : to implement interface functions

class GameObject
{
protected:
	glm::fvec3 position;
	vector <Entity> entities;
	bool show;
public:
	GameObject(vector <Entity> entities, glm::fvec3 position);
	GameObject();
	void hideObject();
	void showObject();
	void rotate(glm::fvec3 rotation);
	void scale(GLfloat times);
	void setPosition(glm::fvec3 position);
	virtual void move(float speed, glm::fvec3 dPos)  {};
	virtual void render(Renderer * renderer, StaticShader shader);
	static vector <GameObject*> getObjects();
	~GameObject();
};
static vector<GameObject*> objects;