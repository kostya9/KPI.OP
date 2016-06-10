#include "CollisionManager.h"

void CollisionManager::collisionProccessing(Player * player, GameObject * object)
{
	Wall * wall = dynamic_cast<Wall *>(object);
	if (wall == nullptr)
		return;


}
