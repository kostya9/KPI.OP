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
		GLuint getUniformLocation(GLchar * unformName);
		virtual void getAllUniformLocations() {};
		virtual void bindAttributes() {};
		void loadFloat(GLuint location, GLfloat value);
		void loadVector(GLuint location, glm::vec3 vec);
		void loadBool(GLuint location, bool value);
		void loadMatrix(GLuint location, glm::mat4 mat);
		void inline bindAttribute(GLuint attrib, const GLchar * varName)
		{
			glBindAttribLocation(programID, attrib, varName);
		}

};

#endif