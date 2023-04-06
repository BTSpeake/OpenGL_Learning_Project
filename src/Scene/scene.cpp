#include "scene.h"

#include <glm/gtx/string_cast.hpp>

Scene::Scene() {
	PlayerCreateInfo playerInf;
	playerInf.eulers = { 0.0f, -90.0f, 0.0f };
	playerInf.position = { 0.0f, 1.0f, 0.0f };
	player = new Player(&playerInf);

	LightCreateInfo lightInf;
	lightInf.col = glm::vec3(1, 1, 1);
	lightInf.pos = glm::vec3(1, 0, 0);
	lightInf.strength = 10.0f; 
	lights.push_back(new Light(&lightInf));

	lightInf.col = glm::vec3(-1, 0, 0);
	lightInf.pos = glm::vec3(0, 1, 0);
	lightInf.strength = 10.0f;
	lights.push_back(new Light(&lightInf));

	lightInf.col = glm::vec3(0, 0, 0);
	lightInf.pos = glm::vec3(0, 2, 1);
	lightInf.strength = 10.0f;
	lights.push_back(new Light(&lightInf));

	// Create the cube object 
	CubeCreateInfo cubeInfo;
	cubeInfo.preT = glm::mat4(1.0f);
	cubeInfo.eulers = { 0.0f, 0.0f, 0.0f };
	cubeInfo.pos = { 0.0f, 0.5f, -10.0f };
	cube = new Cube(&cubeInfo);
}

void Scene::update(float rate) {
	player->update();
	cube->update(rate);

}

void Scene::movePlayer(glm::vec3 dPos) {
	// Check for collision with the cube object
	glm::vec3 plyCbe = cube->pos - (player->position + dPos);
	float d = glm::l2Norm(plyCbe);
	if (d > 3.0) {
		player->position.x += dPos.x;
		player->position.z += dPos.z;
	}
}

void Scene::spinPlayer(glm::vec3 dEuler) {
	player->eulers += dEuler; 
	if (player->eulers.z < 0) {
		player->eulers.z += 360;
	}
	else if (player->eulers.z > 360) {
		player->eulers.z -= 360;
	}
	player->eulers.x = std::max(std::min(player->eulers.x, 89.0f), -89.0f);
}

Scene::~Scene() {

}