#pragma once
#include "Loader.h"
#include "guiTexture.h"
#include <algorithm>
#include <vector>
#include "GuiShader.h"
#include "MenuOption.h"
#include "PickerShader.h"
class GuiRenderer
{
private:
	Model quad;
	GuiShader shader;
	PickerShader picker = PickerShader();
	
public:
	GuiRenderer() {}
	GLuint getIdOnMousePosition(vector<MenuOption *> options);
	GuiRenderer(Loader * loader);
	void render(vector<GuiTexture> textures);
};