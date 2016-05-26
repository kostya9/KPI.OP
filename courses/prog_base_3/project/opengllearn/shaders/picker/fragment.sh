#version 400 core

out vec4 out_Color;

uniform vec3 pickerColor;

void main(){

    out_Color = vec4(pickerColor, 1.0f);

}