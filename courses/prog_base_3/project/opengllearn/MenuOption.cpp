#include "MenuOption.h"

MenuOption::MenuOption(Font * font, vector<Entity> entities, glm::fvec3 color, string text)
{
	this->color = color;
	this->font = font;
	this->entities = entities;
	this->text = text;
	this->scale = 1.0f;
}

void MenuOption::setMenu(Menu * menu)
{
	this->menu = menu;
}

void MenuOption::onSelect()
{
	selected = true;
}

void MenuOption::onDeselect()
{
	selected = false;
}

void MenuOption::render(Renderer * renderer, StaticShader shader, glm::fvec2 position)
{
	for (Entity &en : entities)
	{
		en.position = glm::fvec3(position.x, 6.0f, position.y);
		if (selected)
			en.scale = this->scale + 0.1f;
		else
			en.scale = this->scale;
	}

	for (Entity en : entities)
		renderer->render(en, shader);
	position.x *= Window::getWidth();
	position.y *= Window::getHeight();
	position.x += Window::getWidth() / 2 - text.size() * 15.0f;
	position.y += Window::getHeight()/2 - 12.0f;
	if (!selected)
		font->renderText((GLchar *)text.c_str(), position, color, 1.0f);
	else
	{
		position.y += 1.2f;
		position.x -= 10.0f;
		font->renderText((GLchar *)text.c_str(), position, color, 1.05f);
	}
}

void MenuOption::disable()
{
	enabled = false;
}

void MenuOption::enable()
{
	enabled = true;
}
