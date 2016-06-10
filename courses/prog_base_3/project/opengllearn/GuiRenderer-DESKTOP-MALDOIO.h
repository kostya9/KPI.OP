#pragma once
#include "Loader.h"
#include "guiTexture.h"
#include <algorithm>
#include <vector>
#include "GuiShader.h"
class GuiRenderer
{
private:
	Model quad;
	GuiShader shader;
	
public:
	GuiRenderer() {};
	GuiRenderer(Loader * loader);
	void render(vector<GuiTexture> textures);
};