#version 330 core

uniform float time;

uniform mat4 T;
uniform mat4 Rx;
uniform mat4 Ry;
uniform mat4 Rz;

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 TexCoord;

out vec3 interpolatedNormal;
out vec2 st;
out vec3 lightDirection;

void main() {
	lightDirection = vec3(Ry * Rz);
	gl_Position = vec4(Position, 1); // Special, required output
	vec3 transformedNormal = Normal; //mat3(Ry * Rx) * Normal;
	interpolatedNormal = normalize(transformedNormal);
	st = TexCoord; // Will also be interpolated across the triangle
}