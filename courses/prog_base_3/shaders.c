#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
#include "shaders.h"

#define BUFFER_SIZE 2000
#define VERBOSE 1

struct shader_s
{
    GLuint program;
};

shader_t shader_new(const GLchar* vertexPath, const GLchar* fragmentPath)
{
    shader_t self = malloc(sizeof(struct shader_s));
    FILE * vertexFile = fopen(vertexPath, "r");
    if(vertexFile == NULL)
    {
        #ifdef VERBOSE
        puts("Vertex file not found");
        #endif // VERBOSE
        return NULL;
    }
    FILE * fragmentFile = fopen(fragmentPath, "r");
    if(vertexFile == NULL)
    {
        #ifdef VERBOSE
        puts("Fragment file not found");
        #endif // VERBOSE
        fclose(vertexFile);
        return NULL;
    }
    /*Reading source code from a file*/
    GLchar buffer[BUFFER_SIZE];


    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];

    // Vertex Shader
    fread(buffer, sizeof(GLchar), BUFFER_SIZE, vertexFile);
    vertex = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vShaderCode = buffer;
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // Print compile errors if any
    #ifdef VERBOSE
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        puts("Vertex shader error : ");
        puts(infoLog);
    };
    #endif // VERBOSE

    // Fragment Shader
    memset(buffer, 0, BUFFER_SIZE);
    fread(buffer, sizeof(char), BUFFER_SIZE, fragmentFile);
    const GLchar* fShaderCode = buffer;
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // Print compile errors if any
    #ifdef VERBOSE
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        puts("Fragment shader error : ");
        puts(infoLog);
    };
    #endif // VERBOSE

    // Shader Program
    self->program = glCreateProgram();
    glAttachShader(self->program, vertex);
    glAttachShader(self->program, fragment);
    glLinkProgram(self->program);
    // Print linking errors if any
    #ifdef VERBOSE
    glGetProgramiv(self->program, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(self->program, 512, NULL, infoLog);
        puts("Linking shader error : ");
        puts(infoLog);
    }
    #endif // VERBOSE
    // Delete the shaders as they're linked into our program now and no longer necessery
    fclose(vertexFile);
    fclose(fragmentFile);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    return self;
}
GLuint shader_get_program(shader_t self)
{
    return self->program;
}
void shader_useProgram(shader_t self)
{
    glUseProgram(self->program);
}
void shader_delete(shader_t self)
{
    free(self);
}

