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
		GLfloat alpha = 1.0f;
	public:
		GameObject(vector <Entity> entities, glm::fvec3 position);
		GameObject();
		void hideObject();
		void showObject();
		glm::fvec3 getPosition() { return position; }
		virtual void rotate(glm::fvec3 rotation);
		void setScale(GLfloat times);
		virtual void setPosition(glm::fvec3 position);
		bool getVisibility();
		virtual void setAlpha(GLfloat alpha);
		virtual void move(float speed, glm::fvec3 dPos)  {};
		virtual void render(Renderer * renderer, StaticShader shader);
		static vector <GameObject*> getObjects();
		~GameObject();
};
static vector<GameObject*> objects;