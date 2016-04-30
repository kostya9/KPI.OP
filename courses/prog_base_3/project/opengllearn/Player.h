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
		enum MOVEMENT_STATE_CODE { MOVE_LEFT, MOVE_FORWARD, MOVE_RIGHT, MOVE_BACKWARD, MOVE_NO } moveState;

		GLfloat energy;
		glm::vec3 dest;
		Camera * cam;
		void setSineHeightPosition();
		const GLfloat height = 0.5f;
		glm::fvec3 getMovementVector();

	public:
		enum PLAYER_MOVE_STATUS {NO_COMMANDS, COLLISION_DETECTED, COLLISION_UNDETECTED};
		Player(Loader * loader, glm::fvec3 position, Camera * c);
		void changeEnergy(int dEnergy);
		Camera * getCamera();
		//PLAYER_MOVE_STATUS move(GameObjectManager * manager = nullptr);
		void render(Renderer * renderer, StaticShader shader);
		bool isMoving();
		void moveLeft();
		void moveRight();
		void moveForward();
		void moveBackwards();
		void moveLeft(GLint times);
		void moveRight(GLint times);
		void moveForward(GLint times);
		void moveBackwards(GLint times);
		void update();
};