#include "Menu.h"
#include "GuiRenderer.h"
#include "guiTexture.h"
#include <cstdlib>
void Menu::checkMouse(GuiRenderer * renderer)
{
	GLuint id;
	if (this->fullScreen != nullptr)
		return this->setSelected(fullScreen->getID());
	id = renderer->getIdOnMousePosition(this->options);
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
			return;
		}
		i++;
	}
	if (this->fullScreen != nullptr)
	{
		this->fullScreen->onSelect();
		this->curSelected = fullScreen->getID();
	}
	this->curSelected = -1;
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

void Menu::deleteMenuOption(MenuOption* option)
{
	size_t count = options.size();
	for (int i = 0; i < count; ++i)
	{
		if(option == options.at(i))
		{
			options.erase(options.begin() + i);
			break;
		}
	}
}

void Menu::disable()
{
	active = false;
}

void Menu::setFullScreen(MenuOption* option)
{
	delete keyboard;
	keyboard = new Keyboard();
	this->fullScreen = option;
	this->fullScreen->setMenu(this);
}

void Menu::deleteFullSreen()
{
	delete keyboard;
	keyboard = new Keyboard();
	this->fullScreen = nullptr;
}

void Menu::enable()
{
	active = true;
}

int Menu::update()
{
	int rc = OK;
	if(fullScreen != nullptr)
	{
		if (keyboard->isKeyPressed(GLFW_KEY_ENTER) || keyboard->isLeftButtonPressed())
			rc = this->fullScreen->onClick();
	}
	if (rc == RETURN)
		return rc;
	if (curSelected != -1)
	{
		if (keyboard->isKeyPressed(GLFW_KEY_ENTER) || keyboard->isLeftButtonPressed())
			rc = options.at(curSelected)->onClick();
		if (rc == RETURN)
			return rc;
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
	return rc;
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
	if(this->fullScreen != nullptr)
	{
		textures.push_back(fullScreen->getTexture());
		setSelected(fullScreen->getID());
		renderer->render(textures);
		return;
	}
	for (MenuOption * option : options)
	{
		GuiTexture txt = option->getTexture();
		txt.setPosition(startPos * 2.f);
		glm::fvec2 pos = glm::fvec2(Window::getWidth()/2.f, Window::getHeight()/2.f);
		string text = option->getText();
		pos.x += Window::getWidth() * startPos.x;
		pos.y += Window::getHeight() * startPos.y;
		pos.x -= text.size() * 14.0f;
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
