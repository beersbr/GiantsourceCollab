#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec2 position;
layout(location = 1) in vec3 vertColor;

// Values that stay constant for the whole mesh.
uniform mat4 ProjectionViewModel;

out vec4 color;

void main(){

    color = vec4(vertColor, 1.0f);

	// Output position of the vertex, in clip space : MVP * position;
	gl_Position =  (ProjectionViewModel) * vec4(position, 0, 1);

}

