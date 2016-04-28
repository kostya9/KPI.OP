#include "Player.h"
#include "math.h"
Player::Player(Loader * loader, glm::fvec3 position, Camera & c) : GameObject(entities, position), cam(c)
{
	vector<TexturedModel> models = loader->objToModel("../opengllearn/models/playerBall/playerBall.obj");

	for (TexturedModel model : models)
		entities.push_back(Entity(model));
	energy = 1.0f;
	float delta = 3.0f;
	moveState = MOVE_NO;
	dest = glm::vec3(0.0f, 0.0f, 0.0f);
	cam.setPosition(position);
	cam.moveForward(-delta);
	cam.moveUp(delta);
	// DEBUG
	//cam.yaw(M_PI / 2);
	//cam.moveLeft(3.0f);
	//cam.moveForward(-3.0f);

	cam.pitch(M_PI / 4);
}
void Player::render(Renderer * renderer, StaticShader shader)
{
	glm::vec3 prevPos = this->position;
	setSineHeightPosition();
	GameObject::render(renderer, shader);
	this->setPosition(prevPos);

}
void Player::move(GameObjectManager * manager)
{
	static Wall * wall = nullptr;
	if (moveState == MOVE_NO)
	{
		moveState = getMovementStateFromInputKeys();
		if (moveState == MOVE_NO)
			return;

		wall = getColliderIfAHole(manager);
		if (wall != nullptr)
			wall->setAlpha(0.5f);

		return;
	}
	moveModel(wall);
}

void Player::moveModel(Wall * wall)
{
	glm::fvec3 movement = Player::getMovementVector();
	for (Entity & e : entities)
	{
		movement *= Window::getDeltaTime();
		this->position += movement;
		if (moveState == MOVE_NO)
		{
			if(wall != nullptr)
				wall->setAlpha(1.0f);
			this->setPosition(dest);
			return;
		}
		e.increasePosition(movement);
	}
}

glm::fvec3 Player::getMovementVector()
{
	GLfloat precision = 0.005;
	GLfloat dx = 0;
	GLfloat dz = 0;
	switch (moveState)
	{
		case MOVE_FORWARD:
		{
			dz = -RUN_SPEED;
			float deltaDist = fabs(this->position.z - dest.z);

			if (deltaDist < precision)
			{
				dx = dest.z - this->position.z;
				moveState = MOVE_NO;
			}
		}break;
		case MOVE_BACKWARD:
		{
			dz = RUN_SPEED;
			float deltaDist = fabs(this->position.z - dest.z);
			if (deltaDist < precision)
			{
				dx = dest.z - this->position.z;
				moveState = MOVE_NO;
			}
		}break;
		case MOVE_LEFT:
		{
			dx = -RUN_SPEED;
			float deltaDist = fabs(this->position.x - dest.x);
			if (deltaDist < precision)
			{
				dx = dest.z - this->position.x;
				moveState = MOVE_NO;
			}
		}break;
		case MOVE_RIGHT:
		{
			dx = RUN_SPEED;
			float deltaDist = fabs(this->position.x - dest.x);
			if (deltaDist < precision)
			{
				dx = dest.x - this->position.x;
				moveState = MOVE_NO;
			}
		}
	}
	return glm::fvec3(dx, 0.0f, dz);
}

void Player::setSineHeightPosition()
{
	GLfloat dy = 0.2 * glm::sin(glfwGetTime());
	this->setPosition(glm::vec3(position.x, position.y + dy, position.z));
}

Player::MOVEMENT_STATE_CODE Player::getMovementStateFromInputKeys()
{
	MOVEMENT_STATE_CODE state = MOVE_NO;
	if (keyboard->isKeyPressed('w'))
	{
		dest = glm::vec3(this->position.x, this->position.y, glm::round(this->position.z - 1));
		state = MOVE_FORWARD;
	}
	else if (keyboard->isKeyPressed('s'))
	{
		dest = glm::vec3((this->position.x), this->position.y, glm::round(this->position.z + 1));
		state = MOVE_BACKWARD;
	}
	else if (keyboard->isKeyPressed('a'))
	{
		dest = glm::vec3(glm::round(this->position.x - 1), this->position.y, this->position.z);
		state = MOVE_LEFT;
	}
	else if (keyboard->isKeyPressed('d'))
	{
		dest = glm::vec3(glm::round(this->position.x + 1), this->position.y, this->position.z);
		state = MOVE_RIGHT;
	}
	return state;
}
Wall * Player::getColliderIfAHole(GameObjectManager * manager)
{
	if (manager != nullptr)
	{
		Wall * wall;
		Wall::COLLISION_STATUS status = manager->isMovementColliding(this->position, dest, &wall);
		if (status == Wall::COLLISION_TRUE)
		{
			moveState = MOVE_NO;
			return nullptr;
		}
		else if (status == Wall::COLLISION_HOLE)
		{
			dest += (dest - this->position);
			dest.x = glm::round(dest.x);
			dest.z = glm::round(dest.z);
			return wall;
		}
		else
			return nullptr;
	}
}