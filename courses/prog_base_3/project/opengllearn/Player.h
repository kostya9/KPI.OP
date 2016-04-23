#pragma once
#include "MainHeaders.h"
#include "GameObject.h"
// TODO : to implement interface functions
#define RUN_SPEED 10.0f
#define TURN_SPEED 20.002f
extern Keyboard * keyboard;
class Player : public GameObject
{
	private:
		uint energy;
		GLfloat curSpeed = 0;
		GLfloat curTurnSpeed = 0;
		Camera & cam;
	public:
		Player(vector <Entity> entities, glm::fvec3 position, Camera & c) : GameObject(entities, position), cam(c)
		{};
		void changeEnergy(int dEnergy);
		void move();
};