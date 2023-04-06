#include "engine.h"

Engine::Engine(int w, int h) {
	shader = util::load_shader("Resources/Shaders/vertex_main.txt", "Resources/Shaders/frag_main.txt");
	glUseProgram(shader);

	float aspectRatio = (float)w / (float)h; 
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glm::mat4 projM = glm::perspective(45.0f, aspectRatio, 0.1f, 100.0f);
	glUniformMatrix4fv(
		glGetUniformLocation(shader, "proj"),
		1, GL_FALSE, glm::value_ptr(projM)
	);

	std::stringstream location;
	for (int i = 0; i < 3; i++) {
		location.str("");
		location << "light[" << i << "].col";
		lights.colLoc[i] = glGetUniformLocation(shader, location.str().c_str());
		location.str("");
		location << "light[" << i << "].pos";
		lights.posLoc[i] = glGetUniformLocation(shader, location.str().c_str());
		location.str("");
		location << "light[" << i << "].strength"; 
		lights.strLoc[i] = glGetUniformLocation(shader, location.str().c_str());
	}

	camPosLoc = glGetUniformLocation(shader, "camPos");
	viewLoc = glGetUniformLocation(shader, "view");
	modelLoc = glGetUniformLocation(shader, "model");

	//skyBox = SkyBox();
	//glUseProgram(skyBox.shader);
	//glUniformMatrix4fv(
	//	glGetUniformLocation(skyBox.shader, "proj"),
	//	1, GL_FALSE, glm::value_ptr(projM)
	//);

}

void Engine::render(Scene* scene) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//skyBox.render(scene);
	
	glUseProgram(shader);
	glm::mat4 viewM{
		glm::lookAt(
			scene->player->position,
			scene->player->position + scene->player->forwards,
			scene->player->up
		)
	};
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewM));

	//glm::mat4 modelM{ glm::mat4(1.0f) };
	//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelM));

	glUniform3fv(camPosLoc, 1, glm::value_ptr(scene->player->position));
	int i{ 0 };
	for (Light* light : scene->lights) {
		glUniform3fv(lights.colLoc[i], 1, glm::value_ptr(light->col));
		glUniform3fv(lights.posLoc[i], 1, glm::value_ptr(light->pos));
		glUniform1f(lights.strLoc[i], light->strength);
		++i;
	}
	scene->cube->render(shader);
}

Engine::~Engine() {
	glDeleteProgram(shader);
}