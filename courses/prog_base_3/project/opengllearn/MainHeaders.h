#pragma once
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <cmath>
#include <vector>
#include <algorithm>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include <SOIL.h> // image thing

// GLM Mathematics
#include <glm/glm.hpp> // vector and matrices thing
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//Debug shit. gDebbugger is pretty cooler.
static void bindVAO(GLuint id)
{
	//puts("Bound VAO");
	glBindVertexArray(id);
};
static void unBindVAO()
{
	//puts("Unbound VAO");
	glBindVertexArray(0);
};
// My headers
