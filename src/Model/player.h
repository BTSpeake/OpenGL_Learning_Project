#pragma once 
#include "../config.h"

struct PlayerCreateInfo {
	glm::vec3 position, eulers;
};

class Player {
public:
	Player(PlayerCreateInfo* createInfo);
	~Player();
	void update();

	glm::vec3 position, eulers, up, forwards, right;
};