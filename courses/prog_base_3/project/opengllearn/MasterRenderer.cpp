#include "MasterRenderer.h"

void MasterRenderer::cleanUp()
{
	for (pair<TexturedModel, vector<Entity> *> pair : entities)
	{
		delete pair.second;
	}
	entities = unordered_map<TexturedModel, vector<Entity> *>();
}

void MasterRenderer::render(Light light, Camera cam)
{
	renderer.prepare();
	shader.use();
	shader.loadLight(light);
	shader.loadViewMatrix(cam);
	renderer.render(entities);



	shader.unUse();
	entities.clear();
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

void MasterRenderer::shake(GLfloat time)
{
	renderer.shake(shader, time);
}
