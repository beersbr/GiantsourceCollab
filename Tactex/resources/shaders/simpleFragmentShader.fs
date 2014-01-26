#version 330 core

in vec4 color;
out vec4 colorF;

void main(){
    colorF = color; // vec4(0.5,0.5,0.5, 0.5);
}
