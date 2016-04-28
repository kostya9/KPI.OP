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
		enum MOVEMENT_STATE_CODE { MOVE_LEFT, MOVE_FORWARD, MOVE_RIGHT, MOVE_BACKWARD, MOVE_NO } moveState;
		glm::vec3 dest;
		//GLfloat curSpeed = 0;
		//GLfloat curTurnSpeed = 0;
		Camera & cam;
		void checkCollisionStatus(GameObjectManager * manager);
		void checkInputKeys();
		glm::fvec3 getMovementVector();
		void setSineHeightPosition();
		void moveModel();
	public:
		Player(Loader * loader, glm::fvec3 position, Camera & c);
		void render(Renderer * renderer, StaticShader shader);
		void changeEnergy(int dEnergy);
		void move(GameObjectManager * manager = nullptr);
};