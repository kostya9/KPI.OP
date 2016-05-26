#pragma once
class Menu;
#include "MasterRenderer.h"
#include "Font.h"
#include "guiTexture.h"
class MenuOption
{
	protected:
		GLuint id;
		Font * font;
		Menu * menu;
		GuiTexture texture;
		string text;
		glm::fvec3 color;
		GLfloat scale;
		bool selected = false;
		bool enabled = true;
		GLfloat alpha = 1.0f;
	public:
		MenuOption(Font * font, GuiTexture texture, glm::fvec3 color, string text);
		void setMenu(Menu * menu);
		string getText();
		GLuint getID();
		virtual void onSelect();
		virtual void onDeselect();
		virtual void onClick() {};
		virtual void update() {};
		void setPosition(glm::fvec2 position);
		//virtual void render(GuiRenderer * renderer, glm::fvec2 position);
		void MenuOption::renderText(glm::fvec2 pos);
		virtual GuiTexture getTexture();
		virtual void disable();
		virtual void enable();
};