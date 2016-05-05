#pragma once
#include "MenuOption.h"
extern Keyboard * keyboard;
class Game;
class Menu
{
	protected:
		unsigned int curSelected = 0;
		vector <MenuOption *> options;
		Game * game;
		Camera * cam;
		Light * light;
		bool active;
	public:
		Menu(Game * game) { 
			options = vector<MenuOption *>(); 
			active = true;
			this->game = game;
			this->cam = new Camera();
			cam->moveUp(7.0f);
			cam->pitch(3.1415f / 2);
			cam->roll(3.1415f);
			this->light = new Light(glm::fvec3(0.0f, 2.0f, 0.0f), glm::fvec3(1.0f, 1.0f, 1.0f));
		};
		bool isActive();
		Game * getGame();
		Camera * getCamera();
		Light * getLight();
		void addMenuOption(MenuOption * option);
		void disable();
		void enable();
		void update();
		void render(Renderer * renderer, StaticShader shader);
};