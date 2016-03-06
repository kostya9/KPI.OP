#pragma once
#include <stdio.h>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#define VERBOSE 1
typedef struct shader_s* shader_t;
shader_t shader_new(const GLchar* vertexPath, const GLchar* fragmentPath);
GLuint shader_get_program(shader_t self);
void shader_useProgram(shader_t self);
void shader_delete(shader_t self);
