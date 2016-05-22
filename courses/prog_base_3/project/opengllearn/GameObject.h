#pragma once
#include "MainHeaders.h"
#include "Renderer.h"
#include "Entity.h"
#include "Shader.h"
#include <glm/gtx/norm.hpp>
#include "MasterRenderer.h"
// TODO : to implement interface functions

class GameObject
{
	protected:
		const GLfloat precision = 0.0003f;
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
		bool isAtPositionNeighborhood(glm::fvec3 position);
		virtual void render(MasterRenderer * renderer);
		~GameObject();
};