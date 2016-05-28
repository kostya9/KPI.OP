#version 400 core

in vec2 textureCoords;
in float curX;

out vec4 out_Color;

uniform sampler2D guiTexture;
uniform float xMax;
uniform float yMax;
void main(void){
	out_Color = texture(guiTexture,textureCoords);
	if(curX > xMax)
		discard;
	if(out_Color.a < 0.5f)
		discard;
}