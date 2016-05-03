#pragma once
#include "MenuOption.h"
extern Keyboard * keyboard;
class Menu
{
	protected:
		unsigned int curSelected = 0;
		vector <MenuOption *> options;
		bool active;
	public:
		Menu() { options = vector<MenuOption *>(); active = true; };
		bool isActive();
		void addMenuOption(MenuOption * option);
		void disable();
		void enable();
		void update();
		void render(Renderer * renderer, StaticShader shader);
};