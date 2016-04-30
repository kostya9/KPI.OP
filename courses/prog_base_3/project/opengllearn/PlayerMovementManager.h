#pragma once
#include "Player.h"
#include "GameObjectManager.h"

enum MOVEMENT_STATUS { MOVE_MOVING, MOVE_NOT_MOVING_COLLISION, MOVE_MOVING_HOLE, MOVE_NOT_MOVING_NO_COMMANDS };
class PlayerMovementManager
{
	public:
		static GameObject * getLastCollider();
		static MOVEMENT_STATUS tryMoveForward(Player * player, GameObjectManager * goManager);
		static MOVEMENT_STATUS tryMoveBackward(Player * player, GameObjectManager * goManager);
		static MOVEMENT_STATUS tryMoveLeft(Player * player, GameObjectManager * goManager);
		static MOVEMENT_STATUS tryMoveRight(Player * player, GameObjectManager * goManager);
		static MOVEMENT_STATUS checkInputKeysForMovement(Player * player, GameObjectManager * goManager);
	private:
		static MOVEMENT_STATUS tryMove(Player * player, GameObjectManager * goManager, glm::fvec3 destination);
		static GameObject * lastCollider;
};