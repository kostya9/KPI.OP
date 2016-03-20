#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>

#include "MainHeaders.h"

class Shader
{
	private:
		GLuint programID;
	public:
		// Constructor generates the shader on the fly
		Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
		GLuint getProgramId();
		void deleteShader();
		// Uses the current shader
		void use();
		void unUse();
	protected:
		virtual void bindAttributes() {};
		void bindAttribute(GLuint attrib, const GLchar * varName);

};

#endif