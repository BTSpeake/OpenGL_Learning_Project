#pragma once 
#include "../config.h"

struct LightCreateInfo {
	glm::vec3 pos, col;
	float strength;
};

class Light {
public:
	Light(LightCreateInfo* createInfo);
	~Light();

	glm::vec3 pos, col;
	float strength;
};