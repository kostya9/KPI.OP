#include "Player.h"

void Player::move()
{
	if (keyboard->isKeyPressed('w'))
		curSpeed = -RUN_SPEED;
	else if (keyboard->isKeyPressed('s'))
		curSpeed = RUN_SPEED;
	if (keyboard->isKeyPressed('a'))
		curTurnSpeed = -TURN_SPEED;
	else if(keyboard->isKeyPressed('d'))
		curTurnSpeed = TURN_SPEED;
	for (Entity & e : entities)
	{
		e.increaseRotation(0.0f, curTurnSpeed * Window::getDeltaTime(), 0.0f);
		GLfloat distance = curSpeed * Window::getDeltaTime();
		GLfloat dx = distance * glm::sin(e.rotY);
		GLfloat dz = distance * glm::cos(e.rotY);
		e.increasePosition(dx, 0.0f, dz);
	}
	curSpeed = 0;
	curTurnSpeed = 0;
}
