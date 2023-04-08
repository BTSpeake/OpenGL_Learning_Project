#include "player.h"

Player::Player(glm::vec3 position, glm::vec3 eulers) {
	this->position = position;
	this->eulers = eulers;
	updateVectors();
}

void Player::updateVectors() {
	forwards = {
		glm::cos(glm::radians(eulers.y)) * glm::cos(glm::radians(eulers.x)),
		glm::sin(glm::radians(eulers.x)),
		glm::sin(glm::radians(eulers.y)) * glm::cos(glm::radians(eulers.x))
	};
	forwards = glm::normalize(forwards);
	glm::vec3 globalUp{ 0.0f, 1.0f, 0.0f };
	right = glm::normalize(glm::cross(forwards, globalUp));
	up = glm::normalize(glm::cross(right, forwards));
}

void Player::movePlayer(glm::vec3 dPos) {
	position.x += dPos.x;
	position.z += dPos.z;
}

void Player::spinPlayer(glm::vec3 dEul) {
	eulers += dEul;
	if (eulers.z < 0) {
		eulers.z += 360;
	}
	else if (eulers.z > 360) {
		eulers.z -= 360;
	}
	eulers.x = std::max(std::min(eulers.x, 89.0f), -89.0f);
}

glm::mat4 Player::getViewMatrix() {
	return glm::lookAt(position, position + forwards, up);
}

Player::~Player() {

}