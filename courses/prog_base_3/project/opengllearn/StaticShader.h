#pragma once
#include "Shader.h"
#include "MainHeaders.h"
class StaticShader : public Shader
{
	public:
		StaticShader() : Shader("shaders/vertex.sh", "shaders/fragment.sh") {} // Actually just constatnt paths
	protected:
		virtual void bindAttributes() override
		{
			bindAttribute(0, "position");
			bindAttribute(1, "textureCoordinate");
		}
};