#version 330 core

in vec3 position;
in vec2 textureCoordinate;

out vec2 out_textureCoordinate;

void main(void)
{
	gl_Position = vec4(position, 1.0f);
	out_textureCoordinate =vec2(textureCoordinate.x, textureCoordinate.y);
}