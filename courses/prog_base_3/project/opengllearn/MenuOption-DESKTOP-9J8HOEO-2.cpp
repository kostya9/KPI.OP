#include "MenuOption.h"

MenuOption::MenuOption(Font * font, GuiTexture texture, glm::fvec3 color, string text)
{
	this->color = color;
	this->font = font;
	this->texture = texture;
	this->text = text;
	this->scale = 1.0f;
	this->alpha = 1.0f;
}

void MenuOption::setMenu(Menu * menu)
{
	this->menu = menu;
}

string MenuOption::getText()
{
	return text;
}

GLuint MenuOption::getID()
{
	return id;
}

void MenuOption::onSelect()
{
	selected = true;
}

void MenuOption::onDeselect()
{
	selected = false;
}

void MenuOption::setPosition(glm::fvec2 position)
{
	this->texture.setPosition(position);
}

/*void MenuOption::render(GuiRenderer * renderer, glm::fvec2 position)
{
	for (Entity &en : entities)
	{
		en.alpha = 0.8f;
		en.position = glm::fvec3(position.x, 6.0f, position.y);
		if (selected)
			en.scale = this->scale + 0.1f;
		else
			en.scale = this->scale;
	}

	for (Entity en : entities)
		renderer->proccessEntity(en);
}*/
void MenuOption::renderText(glm::fvec2 pos) {
	pos.x *= Window::getWidth();
	pos.y *= Window::getHeight();
	pos.x += Window::getWidth() / 2 - text.size() * 15.0f;
	pos.y += Window::getHeight() / 2 - 12.0f;
	if (!selected)
		font->renderText((GLchar *)text.c_str(), pos, color, 1.0f);
	else
	{
		pos.y += 1.2f;
		pos.x -= 10.0f;
		font->renderText((GLchar *)text.c_str(), pos, color, 1.05f);
	}
}
GuiTexture MenuOption::getTexture()
{
	return texture;
}
void MenuOption::disable()
{
	enabled = false;
}

void MenuOption::enable()
{
	enabled = true;
}
