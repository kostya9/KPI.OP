#include "Player.h"
#include "math.h"
Player::Player(Loader * loader, glm::fvec3 position, Camera & c) : GameObject(entities, position), cam(c)
{
	vector<TexturedModel> models = loader->objToModel("../opengllearn/models/playerBall/playerBall.obj");

	for (TexturedModel model : models)
		entities.push_back(Entity(model));
	energy = 1.0f;
	float delta = 3.0f;
	moveState = NO;
	cam.setPosition(position);
	cam.moveForward(-delta);
	cam.moveUp(delta);
	// DEBUG
	//cam.yaw(M_PI / 2);
	//cam.moveLeft(3.0f);
	//cam.moveForward(-3.0f);

	cam.pitch(M_PI / 4);
}
void Player::move(GameObjectManager * manager)
{
	if (moveState == NO)
	{
		if (keyboard->isKeyPressed('w'))
		{
			dest = glm::vec3(this->position.x, this->position.y, glm::round(this->position.z - 1));
			moveState = FORWARD;
		}
		else if (keyboard->isKeyPressed('s'))
		{
			dest = glm::vec3((this->position.x), this->position.y, glm::round(this->position.z + 1));
			moveState = BACKWARD;
		}
		else if (keyboard->isKeyPressed('a'))
		{
			dest = glm::vec3(glm::round(this->position.x - 1), this->position.y, this->position.z);
			moveState = LEFT;
		}
		else if (keyboard->isKeyPressed('d'))
		{
			dest = glm::vec3(glm::round(this->position.x + 1), this->position.y, this->position.z);
			moveState = RIGHT;
		}
		else
			return;
		if (manager != nullptr)
		{
			Wall::COLLISION_STATUS status = manager->isMovementColliding(this->position, dest);
			if (status == Wall::COLLISION_TRUE)
			{
				moveState = NO;
				return;
			}
			else if (status == Wall::COLLISION_HOLE)
			{
				dest += (dest - this->position);
				return;
			}
		}
		return;
	}
	GLfloat precision = 0.005;
	GLfloat dx = 0;
	GLfloat dz = 0;
	switch(moveState)
	{
		case FORWARD:
		{
			dz = -RUN_SPEED;
			float deltaDist = fabs(this->position.z - dest.z);

			if (deltaDist < precision)
			{
				dx = dest.z - this->position.z;
				moveState = NO;
			}
		}break;
		case BACKWARD:
		{
			dz = RUN_SPEED;
			float deltaDist = fabs(this->position.z - dest.z);
			if (deltaDist < precision)
			{
				dx = dest.z - this->position.z;
				moveState = NO;
			}
		}break;
		case LEFT:
		{
			dx = -RUN_SPEED;
			float deltaDist = fabs(this->position.x - dest.x);
			if (deltaDist < precision)
			{
				dx = dest.z - this->position.x;
				moveState = NO;
			}
		}break;
		case RIGHT:
		{
			dx = RUN_SPEED;
			float deltaDist = fabs(this->position.x - dest.x);
			if (deltaDist < precision)
			{
				dx = dest.x - this->position.x;
				moveState = NO;
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
		if (moveState == NO)
		{
			this->setPosition(dest);
			return;
		}
		e.increasePosition(dx, 0.0f, dz);
	}
	
	//curSpeed = 0;
	//curTurnSpeed = 0;
}
