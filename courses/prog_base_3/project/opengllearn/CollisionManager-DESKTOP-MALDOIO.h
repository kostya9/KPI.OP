#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Wall.h"
class CollisionManager
{
	public:
		void collisionProccessing(Player * player, GameObject * object);
	private:
};