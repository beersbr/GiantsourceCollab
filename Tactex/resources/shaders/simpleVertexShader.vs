#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 position;
// layout(location = 1) in vec3 vertColor;
// layout(location = 2) in mat4 model;

uniform mat4 ProjectionViewModel;
uniform vec3 Color;

out vec4 colorV;

void main(){

    colorV = vec4(Color, 1.0f);
	gl_Position = ProjectionViewModel * vec4(position, 1);

}

