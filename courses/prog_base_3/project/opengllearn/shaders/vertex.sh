#version 330 core

in vec3 position;
in vec2 textureCoordinate;

out vec3 color;
out vec2 out_textureCoordinate;	

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
void main(void)
{
	gl_Position = projectionMatrix * viewMatrix * transformationMatrix * vec4(position, 1.0f);
	out_textureCoordinate = vec2(textureCoordinate.x, textureCoordinate.y);
}