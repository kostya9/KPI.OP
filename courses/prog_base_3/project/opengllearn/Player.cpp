#include "Player.h"
#include "math.h"
void Player::move()
{
	if (mov == NO)
	{
		if (keyboard->isKeyPressed('w'))
			mov = FORWARD, dest = glm::vec3(this->position.x, this->position.y, glm::round(this->position.z - 1));
		else if (keyboard->isKeyPressed('s'))
			mov = BACKWARD, dest = glm::vec3((this->position.x), this->position.y, glm::round(this->position.z + 1));
		else if (keyboard->isKeyPressed('a'))
			mov = LEFT, dest = glm::vec3(glm::round(this->position.x - 1), this->position.y, this->position.z);
		else if (keyboard->isKeyPressed('d'))
			mov = RIGHT, dest = glm::vec3(glm::round(this->position.x + 1), this->position.y, this->position.z);
		return;
	}
	GLfloat precision = 0.005;
	GLfloat dx = 0;
	GLfloat dz = 0;
	switch (mov)
	{
		case FORWARD:
		{
			dz = -RUN_SPEED;
			float deltaDist = fabs(this->position.z - dest.z);

			if (deltaDist < precision)
			{
				dx = dest.z - this->position.z;
				mov = NO;
			}
		}break;
		case BACKWARD:
		{
			dz = RUN_SPEED;
			float deltaDist = fabs(this->position.z - dest.z);
			if (deltaDist < precision)
			{
				dx = dest.z - this->position.z;
				mov = NO;
			}
		}break;
		case LEFT:
		{
			dx = -RUN_SPEED;
			float deltaDist = fabs(this->position.x - dest.x);
			if (deltaDist < precision)
			{
				dx = dest.z - this->position.x;
				mov = NO;
			}
		}break;
		case RIGHT:
		{
			dx = RUN_SPEED;
			float deltaDist = fabs(this->position.x - dest.x);
			if (deltaDist < precision)
			{
				dx = dest.x - this->position.x;
				mov = NO;
			}
		}
	}
	for (Entity & e : entities)
	{
		/*e.increaseRotation(0.0f, curTurnSpeed * Window::getDeltaTime(), 0.0f);
		GLfloat distance = curSpeed * Window::getDeltaTime();
		GLfloat dx = distance * glm::sin(e.rotY);
		GLfloat dz = distance * glm::cos(e.rotY);*/
		dx *= Window::getDeltaTime();
		dz *= Window::getDeltaTime();
		this->position.x += dx;
		this->position.z += dz;
		if (mov == NO)
		{
			this->setPosition(dest);
			return;
		}
		e.increasePosition(dx, 0.0f, dz);
	}
	
	//curSpeed = 0;
	//curTurnSpeed = 0;
}
