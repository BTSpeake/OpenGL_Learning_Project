#version 450 core 

out vec4 fCol; 

in vec3 fTex;

uniform samplerCube skybox;

void main() {
	fCol = texture(skybox, fTex);
}