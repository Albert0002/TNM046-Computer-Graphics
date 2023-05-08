#version 330 core

uniform float time;

in vec3 interpolatedNormal;
in vec2 st;

out vec4 finalcolor;
in vec3 lightDirection;

vec3 Ia = vec3(0.0, 0.0, 1.0);
vec3 ka = vec3(0.0, 0.0, 1.0);
vec3 Id = vec3(1, 1, 1);
vec3 kd = vec3(1, 1, 1);
vec3 Is = vec3(0.6, 0.6, 0.6);
vec3 ks = vec3(0.6, 0.6, 0.6);
float n = 20;

void main() {
	finalcolor = vec4(1.0, 1.0, 1.0, 1.0);
	//finalcolor = vec4(interpolatedNormal * 0.5 + 0.5, 1.0);
	
	
	/*
	vec3 R = 2.0 * dot(interpolatedNormal, lightDirection) * interpolatedNormal - lightDirection;
	float dotRV = max(dot(R, vec3(0.0, 0.0, 1.0)), 0.0);
	float dotNL = max(dot(interpolatedNormal, lightDirection), 0.0);
	if (dotNL == 0.0) {
		dotRV == 0.0;
	}
	vec3 shadedcolor = Ia * ka + Id * kd * dotNL + Is * ks * pow(dotRV, n);
	
	float dotNL = max(dot(interpolatedNormal, lightDirection), 0.0);
	vec3 shadedcolor = Ia * ka + Id * kd * dotNL;
	finalcolor = vec4(shadedcolor, 1.0);
	*/
	
	//float shading = dot(interpolatedNormal, lightDirection);
	//shading = max(0.0, shading); //Clamp negative values to 0.0
	//finalcolor = vec4(vec3(shading), 1.0);
	//vec3 normalizedNormal = normalize(interpolatedNormal);
	//finalcolor = vec4(vec3(normalizedNormal.z), 1.0);
}