#include "Menu.h"
#include "GuiRenderer.h"
#include "guiTexture.h"
#include <cstdlib>
void Menu::checkMouse(GuiRenderer * renderer)
{
	GLuint id = renderer->getIdOnMousePosition(this->options);
	this->setSelected(id);
}
void Menu::setSelected(int id)
{
	int i = 0;
	for (MenuOption * option : options)
	{
		if (option->getID() == id)
		{
			this->curSelected = i;
			break;
		}
		i++;
	}
}
bool Menu::isActive()
{
	return active;
}

Game * Menu::getGame()
{
	return game;
}

Camera * Menu::getCamera()
{
	return cam;
}

Light * Menu::getLight()
{
	return light;
}

void Menu::addMenuOption(MenuOption * option)
{
	options.push_back(option);
	option->setMenu(this);
}

void Menu::disable()
{
	active = false;
}

void Menu::enable()
{
	active = true;
}

void Menu::update()
{
	if (keyboard->isKeyPressed(GLFW_KEY_ENTER) || keyboard->isLeftButtonPressed())
		options.at(curSelected)->onClick();
	static char prevKey = '\0';
	if ((prevKey == '\0') && keyboard->isKeyPressed('s'))
	{
		options.at(curSelected)->onDeselect();
		curSelected = (curSelected + 1) % (options.size());
		options.at(curSelected)->onSelect();
		prevKey = 's';
	}
	else if ((prevKey == '\0') && keyboard->isKeyPressed('w'))
	{
		options.at(curSelected)->onDeselect();
		curSelected = (curSelected + (options.size() - 1)) % (options.size());
		options.at(curSelected)->onSelect();
		prevKey = 'w';
	}

	if ((prevKey == 'w') && (keyboard->isKeyPressed('w') == false))
		prevKey = '\0';
	else if ((prevKey == 's') && (keyboard->isKeyPressed('s') == false))
		prevKey = '\0';
}
bool isEqual(GLchar x, GLchar y, GLchar precision)
{
	return abs(x - y) < precision;
}
void Menu::render(GuiRenderer * renderer)
{
	/*shader.use();
	shader.loadViewMatrix(c);
	shader.loadLight(light);
	shader.unUse();
	renderer->prepare();*/
	vector<GuiTexture> textures;

	vector<tuple<glm::fvec2, GLfloat, string>> guiText;
	glm::fvec2 startPos = glm::fvec2(0.0f, 0.3f);
	int i = 0;
	for (MenuOption * option : options)
	{
		GuiTexture txt = option->getTexture();
		txt.setPosition(startPos * 2.f);
		glm::fvec2 pos = glm::fvec2(Window::getWidth()/2.f, Window::getHeight()/2.f);
		string text = option->getText();
		pos.x += Window::getWidth() * startPos.x;
		pos.y += Window::getHeight() * startPos.y;
		pos.x -= text.size() * 15.0f;
		pos.y -= 12.0f;
		option->setPosition(startPos * 2.f);
		if (curSelected != i)
		{
			guiText.push_back(make_tuple(pos, 1.0f, text));
			txt.setScale(1.0f);
		}
		else
		{
			//pos.y += 1.2f;
			//pos.x -= 10.0f;
			guiText.push_back(make_tuple(pos, 1.05f, text));
			txt.setScale(1.05f);
		}
		//printf("ID : %i", id);
		textures.push_back(txt);
		//option->render(renderer, startPos);
		startPos.y -= 0.2f;
		i++;
	}
	for (tuple <glm::fvec2, GLfloat, string> obj : guiText)
	{
		font->renderText((GLchar *)get<string>(obj).c_str(), get<glm::fvec2>(obj), glm::fvec3(1.f, 1.f, 1.f), get<GLfloat>(obj));
	}
	renderer->render(textures);
}

void Menu::renderText()
{
	glm::fvec2 startPos = glm::fvec2(0.0f, 0.3f);
	for (MenuOption * opt : options)
	{
		opt->renderText(startPos);
		startPos.y -= 0.2f;
	}
}
