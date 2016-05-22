#pragma once
#include <algorithm>
#include <vector>
#include <unordered_map>
#include "MainHeaders.h"
#include "StaticShader.h"
#include "TexturedModel.h"
#include "Model.h"
#include "Entity.h"
class Renderer
{
private:
	const GLfloat FOV = 70.0f;
	const GLfloat NEAR_PLANE = 0.1f;
	const GLfloat FAR_PLANE = 1000.0f;// WTF>????????????
	GLfloat time = 0;
	glm::fmat4 projectionMatrix;
	StaticShader shader;
	void createProjectionMatrix();
	public:
		Renderer(StaticShader shader);
		/*Prepares the window for drawing the next frame*/
		void prepare();
		/*Renders(draws) a model to the screen*/
		void shake(StaticShader shader, GLfloat time);
		void unShake(StaticShader shader);
		void update(StaticShader shader);
		void render(unordered_map<TexturedModel, vector<Entity> *> entities);
		void render(Shader shader, Entity entity);
		void prepareTexturedModel(TexturedModel text_model);
		void unbindTexturedModel();
		void prepareInstance(Entity entity);
};