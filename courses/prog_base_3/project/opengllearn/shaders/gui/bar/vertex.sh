#version 400 core

in vec2 position;
out float curX;
out vec2 textureCoords;

uniform mat4 transformationMatrix;
uniform float xMax;
uniform float yMax;
void main(void){
	gl_Position = transformationMatrix * vec4(position, 0.0, 1.0);
	curX = gl_Position.x;
	textureCoords = vec2((position.x+1.0)/2.0, 1 - (position.y+1.0)/2.0);
}