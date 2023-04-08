#pragma once
#include "../config.h"

class Player {
public:
	Player(glm::vec3 position, glm::vec3 eulers);
	~Player();
	void updateVectors();
	void movePlayer(glm::vec3 dPos);
	void spinPlayer(glm::vec3 dEul);
	glm::mat4 getViewMatrix();

	glm::vec3 position, eulers, up, forwards, right;
};