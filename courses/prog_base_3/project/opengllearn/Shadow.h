#pragma once
#include "GameObject.h"
#include <queue>
class Shadow : public GameObject{
private:
	queue<glm::fvec3> positions;
public:
	Shadow(Loader * loader, glm::fvec3 position);
	void queuePosition(glm::fvec3 pos);
	void update();
};