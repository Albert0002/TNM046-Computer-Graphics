#version 330 core

uniform float time;

out vec4 finalcolor;
in vec3 interpolatedColor;

void main() {
	finalcolor = vec4(interpolatedColor * (sin(time) + 1), 1.0);
}