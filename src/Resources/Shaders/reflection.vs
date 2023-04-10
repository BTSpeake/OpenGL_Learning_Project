#version 450 core 

layout (location = 0) in vec3 vPos; 
layout (location = 2) in vec3 vNorm;

out vec3 fNorm; 
out vec3 fPos; 

uniform mat4 model; 
uniform mat4 view; 
uniform mat4 proj; 

void main() {
	fNorm = mat3(transpose(inverse(model))) * vNorm; 
	fPos = vec3(model * vec4(vPos, 1.0));
	gl_Position = proj * view * vec4(fPos, 1.0);
}