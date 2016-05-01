#pragma once
#include "MainHeaders.h"
#include "GameObject.h"
#include "Shader.h"
#include "Wall.h"
#include "Player.h"
#include "Field.h"
class GameObjectManager
{
	private:
		vector<GameObject *> objects;
		vector <Wall *> walls;
		Field * field;
		Player * player;
		Light * light;
		Renderer * renderer;
		StaticShader * shader;
	public:
		GameObjectManager();
		Wall::COLLISION_STATUS isMovementColliding(glm::fvec3 positionFrom, glm::fvec3 positionDest, Wall ** collider); // Wall collision
		void renderAll();
		void addObject(Wall * wall);
		void addObject(Player * player);
		void addObject(Field * field);
		void addObject(GameObject * object);
		void addObject(Light * light);
		Field * getField();
		Light * getLight();
		Player * getPlayer();
		void deleteObject(GameObject * object);
		~GameObjectManager();

};