#version 450 core 

out vec4 fCol; 

in vec3 fNorm; 
in vec3 fPos; 

uniform vec3 camPos; 
uniform samplerCube skybox; 

void main() {
	// Create reflection of skybox on object
	vec3 I = normalize(fPos - camPos);
	vec3 R = reflect(I, normalize(fNorm));
	fCol = vec4(texture(skybox, R).rgb, 1.0);
	// Add red highlight 
	fCol = fCol + vec4(0.2, 0.0, 0.0, 0.0);
}