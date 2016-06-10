#include "MasterRenderer.h"

void MasterRenderer::prepare()
{
	renderer.prepare();
}

void MasterRenderer::cleanUp()
{
	for (pair<TexturedModel, vector<Entity> *> pair : entities)
	{
		delete pair.second;
	}
	entities.clear();
	entities = unordered_map<TexturedModel, vector<Entity> *>();
}

void MasterRenderer::render(Shader shader, Entity entity)
{
	renderer.render(shader, entity);
}

void MasterRenderer::render(Light * light, Camera * cam)
{
	renderer.prepare();
	if (timeLeft > 0)
	{
		renderer.addMask(blinkColor/2.f + (blinkColor/2.f) * glm::cos(timeLeft * 1.2f));
		timeLeft -= Window::getDeltaTime();
	}
	else if(timeLeft < 0)
	{
		renderer.addMask(glm::fvec3(1.0f, 1.0f, 1.0f));
		timeLeft = 0;
	}
	shader.use();
	shader.loadLight(light);
	shader.loadViewMatrix(cam);
	renderer.render(entities);
	shader.unUse();
}

void MasterRenderer::proccessEntity(Entity entity)
{
	TexturedModel entityModel = entity.model;
	vector<Entity> * ents = entities[entityModel];
	if (ents == NULL)
	{
		ents = new vector<Entity>;
		//entities.emplace(entityModel, ents);
		entities[entityModel] = ents;
	}
	ents->push_back(entity);
	
}

void MasterRenderer::update()
{
	renderer.update(shader);
}

void MasterRenderer::mask(glm::fvec3 color)
{
	renderer.addMask(color);
}

void MasterRenderer::shake(GLfloat time)
{
	renderer.shake(shader, time);
}

void MasterRenderer::blinkMask(glm::fvec3 color)
{
	if (timeLeft <= 0)
	{
		this->timeLeft = blinkTime;
		this->blinkColor = color;
	}
}
