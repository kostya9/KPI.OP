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

		void moveModel(Wall * wall);

		Player::MOVEMENT_STATE_CODE getMovementStateFromInputKeys();
		glm::fvec3 getMovementVector();
		Wall::COLLISION_STATUS getColliderIfAHole(GameObjectManager * manager, Wall ** wall);
		void setSineHeightPosition();

	public:
		enum PLAYER_MOVE_STATUS {NO_COMMANDS, COLLISION_DETECTED, COLLISION_UNDETECTED};
		Player(Loader * loader, glm::fvec3 position, Camera * c);
		void changeEnergy(int dEnergy);
		Camera * getCamera();
		PLAYER_MOVE_STATUS move(GameObjectManager * manager = nullptr);
		void render(Renderer * renderer, StaticShader shader);

};