#version 330 core

in vec3 position;

out vec3 color;

void main(void)
{
	gl_Position = vec4(position, 1.0f);
	color = vec3(position.x + 0.5f, 1.0f, position.y + 0.5f);
}