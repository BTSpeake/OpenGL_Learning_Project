#include "light.h"

#include <glm/gtx/string_cast.hpp>

Light::Light(LightCreateInfo* createInfo) {
	this->pos = createInfo->pos;
	this->col = createInfo->col;
	this->strength = createInfo->strength;
}

void Light::addLightToShader(unsigned int shader) {
	
	//std::cout << "Shader: " << shader << std::endl;
	//std::cout << "Position: " << glm::to_string(pos) << std::endl;
	//std::cout << "Colour: " << glm::to_string(col) << std::endl;
	//std::cout << "Strength: " << strength << std::endl;
	glUseProgram(shader);
	glUniform3fv(glGetUniformLocation(shader, "light.pos"), 1, glm::value_ptr(pos));
	glUniform3fv(glGetUniformLocation(shader, "light.col"), 1, glm::value_ptr(col));
	glUniform1f(glGetUniformLocation(shader, "light.strength"), strength);
}