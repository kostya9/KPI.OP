#include "WallHole.h"

WallHole::WallHole(vector<Entity> entities, glm::fvec3 position) : GameObject(entities, position)
{

}

WallHole::HOLE_DIRECTION WallHole::getDirection()
{
	return direction;
}

void WallHole::render(Renderer * renderer, StaticShader shader)
{
	if (!show) // This is a hole, so invisibility for it means that Entities should be visible
		for (Entity en : entities)
		{
			renderer->render(en, shader);
		}
}

WallHole::VISIBILITY_RETURN_CODE WallHole::makeVisible(HOLE_DIRECTION direction)
{
	this->show = true;
	if (this->direction == direction)
		return VISIBILITY_DONE_NOTHING;

	this->rotate(glm::vec3(0.0f, 90.0f, 0.0f));
	this->direction = direction;

	return VISIBILITY_ROTATION_CHANGED;
}

WallHole::VISIBILITY_RETURN_CODE WallHole::makeInvisible()
{
	this->show = false;
	return VISIBILITY_DONE_INVISIBLE;
}
