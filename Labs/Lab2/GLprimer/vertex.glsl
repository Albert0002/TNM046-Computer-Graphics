#version 330 core

uniform float time;

uniform mat4 T;
uniform mat4 R;

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Color;
out vec3 interpolatedColor;

void main() {
	gl_Position = R * T * vec4(Position, 1); 
	interpolatedColor = Color; //Pass intepolated color to fragment shader
}