#pragma once
#include "GameObject.h"
class WallHole : public GameObject{
	public:
		enum VISIBILITY_RETURN_CODE {VISIBILITY_DONE_NOTHING, VISIBILITY_DONE_INVISIBLE, VISIBILITY_ROTATION_CHANGED};
		enum HOLE_DIRECTION { HOLE_DIRECTION_X, HOLE_DIRECTION_Z};

		WallHole(vector<Entity> entities, glm::fvec3 position);
		HOLE_DIRECTION getDirection();
		void render(Renderer * renderer, StaticShader shader);
		VISIBILITY_RETURN_CODE makeVisible(HOLE_DIRECTION direction);
		VISIBILITY_RETURN_CODE makeInvisible();
	private:
		HOLE_DIRECTION direction = HOLE_DIRECTION_Z;

};