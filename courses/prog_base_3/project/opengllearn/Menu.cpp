#include "Menu.h"

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
	if (keyboard->isKeyPressed(GLFW_KEY_ENTER))
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

void Menu::render(MasterRenderer * renderer)
{
	/*shader.use();
	shader.loadViewMatrix(c);
	shader.loadLight(light);
	shader.unUse();
	renderer->prepare();*/
	glm::fvec2 startPos = glm::fvec2(0.0f, 0.3f);
	for (MenuOption * option : options)
	{
		option->render(renderer, startPos);
		startPos.y -= 0.2f;
	}
}