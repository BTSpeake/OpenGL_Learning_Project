#version 450 core 

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vTex;
layout (location = 2) in vec3 vNorm;

out vec2 fTex; 
out vec3 fPos;
out vec3 fNorm; 

uniform mat4 model;
uniform mat4 view; 
uniform mat4 proj;

void main() {
	gl_Position = proj * view * model * vec4(vPos, 1.0);
	fTex = vec2(vTex.x, 1.0 - vTex.y);
	fPos = (model * vec4(vPos, 1.0)).xyz; 
	fNorm = mat3(model) * vNorm; 
}