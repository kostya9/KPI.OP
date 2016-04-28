#pragma once
#include "MainHeaders.h"
#include "GameObject.h"
#include "Shader.h"
#include "Wall.h"
class GameObjectManager
{
	private:
		vector<GameObject *> objects;
		vector <Wall *> walls;
	public:
		Wall::COLLISION_STATUS isMovementColliding(glm::fvec3 positionFrom, glm::fvec3 positionDest); // Wall collision
		void renderAll(Renderer * renderer, StaticShader shader);
		void addObject(Wall * wall);
		void addObject(GameObject * object);
		void deleteObject(GameObject * object);
		~GameObjectManager();

};