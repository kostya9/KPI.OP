#pragma once
#include "MainHeaders.h"
#include "GameObject.h"
#include "Shader.h"
#include "Wall.h"
#include "Player.h"
#include "Field.h"
#include "WhiteHole.h"
#include "Menu.h"
#include "MasterRenderer.h"
class GameObjectManager
{
	private:
		vector<GameObject *> objects;
		vector <Wall *> walls;
		Field * field;
		Player * player;
		WhiteHole * hole;
		Light * light;
		MasterRenderer * renderer;
		/*StaticShader * shader;*/
		Menu * menu;
	public:
		GameObjectManager();
		void shake(GLfloat time);
		Wall::COLLISION_STATUS isMovementColliding(glm::fvec3 positionFrom, glm::fvec3 positionDest, Wall ** collider); // Wall collision
		void renderAll();
		void addObject(Wall * wall);
		void addObject(Player * player);
		void addObject(Field * field);
		void addObject(GameObject * object);
		void addObject(Light * light);
		void addObject(WhiteHole * hole);
		void addObject(Menu * menu);
		WhiteHole * getWhiteHole();
		Field * getField();
		Light * getLight();
		Player * getPlayer();
		void deleteObject(GameObject * object);
		~GameObjectManager();

};