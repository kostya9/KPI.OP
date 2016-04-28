#pragma once
#include "MainHeaders.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#define _USE_MATH_DEFINES
#include <math.h>
// TODO : to implement interface functions
#define RUN_SPEED 1.f
#define TURN_SPEED 20.002f
extern Keyboard * keyboard;
class Player : public GameObject
{
	private:
		GLfloat energy;
		enum MOVEMENT { LEFT, FORWARD, RIGHT, BACKWARD, NO } moveState;
		glm::vec3 dest;
		//GLfloat curSpeed = 0;
		//GLfloat curTurnSpeed = 0;
		Camera & cam;
	public:
		Player(Loader * loader, glm::fvec3 position, Camera & c);
		void render(Renderer * renderer, StaticShader shader)
		{
			GLfloat dy = 0.2 * glm::sin(glfwGetTime());
			glm::vec3 prevPos = this->position;
			this->setPosition(glm::vec3(position.x, position.y + dy, position.z));
			GameObject::render(renderer, shader);
			this->setPosition(prevPos);

		}
		void changeEnergy(int dEnergy);
		void move(GameObjectManager * manager = nullptr);
};