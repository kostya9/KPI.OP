#pragma once
class Menu;
#include "MasterRenderer.h"
#include "Font.h"
class MenuOption
{
	protected:
		Font * font;
		Menu * menu;
		vector<Entity> entities;
		string text;
		glm::fvec3 color;
		GLfloat scale;
		bool selected = false;
		bool enabled = true;
		GLfloat alpha = 1.0f;
	public:
		MenuOption(Font * font, vector<Entity> entities, glm::fvec3 color, string text);
		void setMenu(Menu * menu);
		virtual void onSelect();
		virtual void onDeselect();
		virtual void onClick() {};
		virtual void update() {};
		virtual void render(MasterRenderer * renderer, glm::fvec2 position);
		virtual void disable();
		virtual void enable();
};