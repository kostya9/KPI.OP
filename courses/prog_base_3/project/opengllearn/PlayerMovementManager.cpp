#include "PlayerMovementManager.h"
GameObject * PlayerMovementManager::lastCollider = nullptr;
extern Keyboard * keyboard;


GameObject * PlayerMovementManager::getLastCollider()
{
	return lastCollider;
}
MOVEMENT_STATUS PlayerMovementManager::tryMoveForward(Player * player, GameObjectManager * goManager)
{
	glm::fvec3 dest = player->getPosition() + glm::fvec3(0.0f, 0.0f, -1.0f);
	MOVEMENT_STATUS status = tryMove(player, goManager, dest);
	if (status == MOVE_MOVING_HOLE)
		player->moveForward(2);
	else if (status == MOVE_MOVING)
		player->moveForward(1);
	return status;
}

MOVEMENT_STATUS PlayerMovementManager::tryMoveBackward(Player * player, GameObjectManager * goManager)
{
	glm::fvec3 dest = player->getPosition() + glm::fvec3(0.0f, 0.0f, 1.0f);
	MOVEMENT_STATUS status = tryMove(player, goManager, dest);
	if (status == MOVE_MOVING_HOLE)
		player->moveBackwards(2);
	else if (status == MOVE_MOVING)
		player->moveBackwards(1);
	return status;
}

MOVEMENT_STATUS PlayerMovementManager::tryMoveLeft(Player * player, GameObjectManager * goManager)
{
	glm::fvec3 dest = player->getPosition() + glm::fvec3(-1.0f, 0.0f, 0.0f);
	MOVEMENT_STATUS status = tryMove(player, goManager, dest);
	if (status == MOVE_MOVING_HOLE)
		player->moveLeft(2);
	else if (status == MOVE_MOVING)
		player->moveLeft(1);
	return status;
}

MOVEMENT_STATUS PlayerMovementManager::tryMoveRight(Player * player, GameObjectManager * goManager)
{
	glm::fvec3 dest = player->getPosition() + glm::fvec3(1.0f, 0.0f, 0.0f);
	MOVEMENT_STATUS status = tryMove(player, goManager, dest);
	if (status == MOVE_MOVING_HOLE)
		player->moveRight(2);
	else if (status == MOVE_MOVING)
		player->moveRight(1);
	return status;
}

MOVEMENT_STATUS PlayerMovementManager::checkInputKeysForMovement(Player * player, GameObjectManager * goManager)
{
	if (player->isMoving() == false)
	{
		MOVEMENT_STATUS status;
		if (keyboard->isKeyPressed('w'))
		{
			status = tryMoveForward(player, goManager);
			return status;
		}
		else if (keyboard->isKeyPressed('s'))
		{
			MOVEMENT_STATUS status = tryMoveBackward(player, goManager);
			return status;
		}
		else if (keyboard->isKeyPressed('a'))
		{
			MOVEMENT_STATUS status = tryMoveLeft(player, goManager);
			return status;
		}
		else if (keyboard->isKeyPressed('d'))
		{
			MOVEMENT_STATUS status = tryMoveRight(player, goManager);
			return status;
		}
		else
			return MOVE_NOT_MOVING_NO_COMMANDS;
	}
	else
		return MOVE_MOVING;

}

MOVEMENT_STATUS PlayerMovementManager::tryMove(Player * player, GameObjectManager * goManager, glm::fvec3 destination)
{
	Wall * collider;
	glm::fvec3 playerPosition = player->getPosition();
	Wall::COLLISION_STATUS collision_status = goManager->isMovementColliding(playerPosition, destination, &collider);
	if (collision_status == Wall::COLLISION_TRUE)
	{
		lastCollider = collider;
		glm::fvec3 movementVec = (destination - playerPosition);
		if (goManager->isMovementColliding(playerPosition + movementVec, destination + movementVec, nullptr) == Wall::COLLISION_TRUE)
			return MOVE_NOT_MOVING_COLLISION;
		if (collider->hasHole() == false)
		{
			if (isMovementOffField(goManager, playerPosition, movementVec))
				return MOVE_NOT_MOVING_COLLISION;
			if (player->canBurnWall() == false)
				return MOVE_NOT_ENOUGH_ENERGY;
			showWall(destination, playerPosition, collider);
			player->startDamaging(60);
			return MOVE_MOVING_HOLE;
		}
		else
			return MOVE_NOT_MOVING_COLLISION;
	}
	else if (collision_status == Wall::COLLISION_FALSE)
	{
		if (goManager->getField()->isInField(glm::fvec2(destination.x, destination.z)) == false)
			return MOVE_NOT_MOVING_COLLISION;
		return MOVE_MOVING;
	}
	else if (collision_status == Wall::COLLISION_HOLE)
	{
		lastCollider = collider;
		return MOVE_MOVING_HOLE;
	}
	else
		return MOVE_NOT_MOVING_NO_COMMANDS;
}

bool PlayerMovementManager::isMovementOffField(GameObjectManager * goManager, glm::fvec3 &playerPosition, glm::fvec3 &movementVec)
{
	return goManager->getField()->isInField(glm::fvec2((playerPosition + 2.0f * movementVec).x, (playerPosition + 2.0f * movementVec).z)) == false;
}

void PlayerMovementManager::showWall(glm::fvec3 &destination, glm::fvec3 &playerPosition, Wall * collider)
{
	if (glm::abs(destination.x - playerPosition.x) > 0.5f)
	{
		collider->showHole(WallHole::HOLE_DIRECTION_X);
	}
	else
		collider->showHole(WallHole::HOLE_DIRECTION_Z);
}
