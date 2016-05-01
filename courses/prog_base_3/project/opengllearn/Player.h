#pragma once
#include "MainHeaders.h"
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
		GLfloat energy = 1.0f;
		GLuint dmgPerSecond = 0.0f;
		glm::vec3 dest;
		Camera * cam;
		void setSineHeightPosition();
		const GLfloat height = 0.5f;
		glm::fvec3 getMovementVector();
		void Player::addDamage(GLuint dmg);

	public:
		enum PLAYER_MOVE_STATUS {NO_COMMANDS, COLLISION_DETECTED, COLLISION_UNDETECTED};
		Player(Loader * loader, glm::fvec3 position, Camera * c);
		GLfloat getEnergy();
		Camera * getCamera();
		//PLAYER_MOVE_STATUS move(GameObjectManager * manager = nullptr);
		void render(Renderer * renderer, StaticShader shader);
		void startDamaging(GLuint dmgPerSecond);
		void stopDamaging();
		bool canBurnWall();
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