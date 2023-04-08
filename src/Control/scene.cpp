#include "scene.h"

Scene::Scene(int w, int h) {
	this->w = w;
	this->h = h;
	// Create player/camera 
	glm::vec3 eulers = { 0.0f, -90.0f, 0.0f };
	glm::vec3 position = { 0.0f, 1.0f, 0.0f };
	player = new Player(position, eulers);

	// Make a main shader program 
	mainShader = util::load_shader("Resources/Shaders/main.vs", "Resources/Shaders/main.fs");
	glUseProgram(mainShader);
	glm::mat4 projM = glm::perspective(glm::radians(45.0f), (float)w / (float)h, 0.1f, 100.0f);
	glUniformMatrix4fv(glGetUniformLocation(mainShader, "proj"), 1, GL_FALSE, glm::value_ptr(projM));

	// Make a cube object
	CubeCreateInfo cubeInfo;
	cubeInfo.preT = glm::mat4(1.0f);
	cubeInfo.eulers = { 0.0f, 0.0f, 0.0f };
	cubeInfo.pos = { 0.0f, 0.5f, -10.0f };
	cube = new Cube(&cubeInfo);

	// Make skybox 
	skybox = new SkyBox();
	glUseProgram(skybox->shader);
	glUniformMatrix4fv(glGetUniformLocation(skybox->shader, "proj"), 1, GL_FALSE, glm::value_ptr(projM));

	glEnable(GL_DEPTH_TEST);
}

void Scene::update(float rate) {

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	player->updateVectors();
	
	glm::mat4 viewM = player->getViewMatrix();
	glUseProgram(mainShader);
	glUniformMatrix4fv(glGetUniformLocation(mainShader, "view"), 1, GL_FALSE, glm::value_ptr(viewM));
	
	cube->render(mainShader);

	skybox->render(viewM);
}

Scene::~Scene() {
	
}