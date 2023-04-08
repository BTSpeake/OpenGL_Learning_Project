#version 450 core 

layout (location = 0) in vec3 vPos;

out vec3 fTex;

uniform mat4 proj;
uniform mat4 view;

void main() {
	fTex = vPos;
	vec4 pos = proj * view * vec4(vPos, 1.0);
	gl_Position = pos.xyww;
}