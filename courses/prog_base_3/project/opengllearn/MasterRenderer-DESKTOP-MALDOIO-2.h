#pragma once
#include <algorithm>
#include <vector>
#include <unordered_map>
#include "StaticShader.h"
#include "Renderer.h"
#include "TexturedModel.h"
#include "Entity.h"
using namespace std;
class MasterRenderer
{
private:
	StaticShader shader = StaticShader();
	Renderer renderer = Renderer(shader);
	unordered_map<TexturedModel, vector<Entity> *> entities = unordered_map<TexturedModel, vector<Entity> *>();
public:
	void prepare();
	void cleanUp();
	void render(Shader shader, Entity entity);
	void render(Light * light, Camera * cam);
	void proccessEntity(Entity entity);
	void update();
	void mask(glm::fvec3 color);
	void shake(GLfloat time);
};