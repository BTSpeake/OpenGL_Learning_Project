#version 450 core 

struct PointLight{
	vec3 pos; 
	vec3 col;
	float strength;
};

in vec2 fTex;
in vec3 fPos; 
in vec3 fNorm;

out vec4 finalColour; 
uniform sampler2D basTex; 
uniform PointLight light; 
uniform vec3 camPos; 

void main() {
	vec3 base = texture(basTex, fTex).rgb;
	
	// ambient
	vec3 col = 0.2 * base; 
	
	//geometric data 
	vec3 fragLight = light.pos - fPos;
	float dist = length(fragLight);
	fragLight = normalize(fragLight);
	vec3 fragCam = normalize(camPos - fPos);
	vec3 halfVec = normalize(fragLight + fragCam);
	
	//diffuse 
	col += light.col * base * light.strength * max(0.0, dot(fNorm, fragLight)) / (dist * dist);
	
	//specular 
	col += vec3(1.0) * pow(max(0.0, dot(fNorm, fragLight)), 32) * light.strength / (dist * dist);

	//final colour with alpha channel 
	finalColour = vec4(col, 1.0);
}