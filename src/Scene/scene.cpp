#include "scene.h"

Scene::Scene() {
	PlayerCreateInfo playerInf;
	playerInf.eulers = { 0.0f, 90.0f, 0.0f };
	playerInf.position = { 0.0f, 0.0f, 1.0f };
	player = new Player(&playerInf);

	LightCreateInfo lightInf;
	lightInf.col = glm::vec3(1, 1, 1);
	lightInf.pos = glm::vec3(1, 0, 0);
	lightInf.strength = 10.0f; 
	lights.push_back(new Light(&lightInf));

	lightInf.col = glm::vec3(1, 1, 1);
	lightInf.pos = glm::vec3(1, 0, 0);
	lightInf.strength = 10.0f;
	lights.push_back(new Light(&lightInf));

	lightInf.col = glm::vec3(1, 1, 1);
	lightInf.pos = glm::vec3(1, 0, 0);
	lightInf.strength = 10.0f;
	lights.push_back(new Light(&lightInf));
}

void Scene::update(float rate) {
	player->update();
}

void Scene::movePlayer(glm::vec3 dPos) {
	player->position += dPos;
}

void Scene::spinPlayer(glm::vec3 dEuler) {
	player->eulers += dEuler; 
	if (player->eulers.z < 0) {
		player->eulers.z += 360;
	}
	else if (player->eulers.z > 360) {
		player->eulers.z -= 360;
	}
	player->eulers.y = std::max(std::min(player->eulers.y, 179.0f), 1.0f);
}

Scene::~Scene() {

}