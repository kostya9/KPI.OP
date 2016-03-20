#pragma once
#include "Shader.h"
#include "MainHeaders.h"
class StaticShader : public Shader
{
	public:
		StaticShader() : Shader("shaders/vertex.sh", "shaders/fragment.sh") {}
	protected:
		virtual void bindAttributes() override
		{
			bindAttribute(0, "position");
		}
};