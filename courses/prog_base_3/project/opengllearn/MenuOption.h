#pragma once
class Menu;
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
	public:
		MenuOption(Font * font, vector<Entity> entities, glm::fvec3 color, string text);
		void setMenu(Menu * menu);
		virtual void onSelect();
		virtual void onDeselect();
		virtual void onClick() {};
		virtual void update() {};
		virtual void render(Renderer * renderer, StaticShader shader, glm::fvec2 position);
		virtual void disable();
		virtual void enable();
};