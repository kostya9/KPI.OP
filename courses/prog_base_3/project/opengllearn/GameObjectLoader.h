#pragma once
#include "MainHeaders.h"
#include "GameObjectManager.h"
#include "Field.h"
#include "Player.h"
#include "WhiteHole.h"
// TODO: Remove model loadings from class constructors to here
class GameObjectLoader
{
	public:
		GameObjectLoader(GameObjectManager * manager);
		void generateField(glm::fvec2 center, GLuint size);
		void createPlayer(glm::fvec2 position);
		void createWall(glm::fvec2 position);
		void createLight(GLfloat brightness, glm::fvec3 position);
		void creatWhiteHole(glm::fvec2 position);
		void createShadow(glm::fvec3 position);
		void loadLevel(string path);
		~GameObjectLoader();
	private:
		GameObjectManager * manager;
		Loader * loader;
};