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

	// Create light source 
	LightCreateInfo lightInfo;
	lightInfo.pos = { 0.0f, 1.0f, 0.0f };
	lightInfo.col = { 0.9f, 0.9f, 0.9f };
	lightInfo.strength = 10.0f;
	light = new Light(&lightInfo);
	light->addLightToShader(mainShader);

	// Make a reflective shader program 
	reflectShader = util::load_shader(
		"Resources/Shaders/reflection.vs", "Resources/Shaders/reflection.fs"
	);


	// Make a cube object
	CubeCreateInfo cubeInfo;
	cubeInfo.preT = glm::mat4(1.0f);
	cubeInfo.eulers = { 0.0f, 0.0f, 0.0f };
	cubeInfo.pos = { 0.0f, 0.5f, -10.0f };
	cubeInfo.objPath = "Resources/Mesh/cube.obj";
	cubeInfo.texPath = "Resources/Textures/wood.jpg";
	cube = new Cube(&cubeInfo);

	// Make a reflective sphere object 
	SphereCreateInfo sphrInfo;
	sphrInfo.preT = glm::mat4(1.0f);
	sphrInfo.eulers = { 0.0f, 0.0f, 0.0f };
	sphrInfo.pos = { 5.0f, 1.0f, -10.0f };
	sphrInfo.objPath = "Resources/Mesh/sphere.obj";
	sphere = new Sphere(&sphrInfo);
	sphere->setProjection(projM);

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
	glUniform3fv(glGetUniformLocation(mainShader, "camPos"), 1, glm::value_ptr(player->position));

	cube->render(mainShader);

	sphere->setView(viewM);
	sphere->setCameraPosition(player->position);
	sphere->render(skybox->textureID);

	skybox->render(viewM);
}

Scene::~Scene() {
	delete cube;
	delete player;
	//delete skybox;
	delete light;
}