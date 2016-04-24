#pragma once
#include "MainHeaders.h"
#include "GameObject.h"
class Wall : public GameObject
{
	private:
		vector<Entity> entitiesHole;
		bool holeVisible;
	public:
		Wall(Loader * loader, glm::vec3 position);
		void render(Renderer * renderer, StaticShader shader);
		void setPosition(glm::fvec3 position);
		void showHole();
		void hideHole();

};