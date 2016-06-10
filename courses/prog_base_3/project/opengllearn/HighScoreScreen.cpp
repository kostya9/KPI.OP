#include "HighScoreScreen.h"
#include "Menu.h"
#include "Game.h"

HighScoreScreen::HighScoreScreen(Loader* loader, Font* font, glm::fvec3 color) : MenuOptionButton(loader, font, color, string("High Scores"))
{
	this->texture.setInitialScale(glm::fvec2(0.8f, 0.8f));
	this->id = 1000;
}

int HighScoreScreen::onClick()
{
	this->menu->deleteFullSreen();
	return OK;
}

void HighScoreScreen::onSelect()
{
	glm::fvec2 start = glm::fvec2(Window::getWidth() / 4, Window::getHeight()*8.f / 10);
	font->renderText((GLchar *)"Top 5 highscores : ", start, glm::fvec3(1, 1, 1), 1.0);
	start -= glm::fvec2(0, Window::getHeight() / 10.f);
	start += glm::fvec2(Window::getWidth() / 5, 0);
	Points * pts = this->menu->getGame()->getPoints();
	for(int i = 0; i < 5; i++)
	{
		Entry e = pts->getEntry(i);
		glm::fvec2 delta = glm::fvec2(0, i * Window::getHeight() / 10.f);
		font->renderText((GLchar *)to_string(e.points).c_str(), start - delta, glm::fvec3(1, 1, 1), 1.0);
	}
}
