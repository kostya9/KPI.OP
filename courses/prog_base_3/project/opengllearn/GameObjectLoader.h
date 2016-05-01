#pragma once
#include "MainHeaders.h"
#include "GameObjectManager.h"
#include "Field.h"
#include "Player.h"
// TODO: Remove model loadings from class constructors to here
class GameObjectLoader
{
	public:
		GameObjectLoader(GameObjectManager * manager);
		void generateField(glm::fvec2 center, GLuint size);
		void createPlayer(glm::fvec2 position);
		void createWall(glm::fvec2 position);
		void createLight(GLfloat brightness, glm::fvec3 position);
		~GameObjectLoader();
	private:
		GameObjectManager * manager;
		Loader * loader;
};