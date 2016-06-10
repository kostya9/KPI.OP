#pragma once
#include "MainHeaders.h"
#include "GameObjectManager.h"
#include "Menu.h"
class GameObjectLoader
{
	public:
		GameObjectLoader(GameObjectManager * manager, Font * font);
		void generateField(glm::fvec2 center, GLuint size);
		void createPlayer(glm::fvec2 position);
		void createWall(glm::fvec2 position);
		void createLight(GLfloat brightness, glm::fvec3 position) const;
		void creatWhiteHole(glm::fvec2 position);
		void createShadow(glm::fvec3 position);
		void loadLevel(string path);
		void loadMenu(Game * game);
		~GameObjectLoader();
	private:
		GameObjectManager * manager;
		Font * font;
		Loader * loader;
};