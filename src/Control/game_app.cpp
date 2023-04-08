#include "game_app.h"	

GameApp::GameApp(int w, int h) {
	// Initialisse variables
	this->w = w;
	this->h = h;
	lastTime = glfwGetTime();
	nFrames = 0;
	frameTime = 16.0f;
	currTime = 0.0f;


	// Initialise glfw 
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//// Create the glfw window 
	window = glfwCreateWindow(w, h, "OpenGL Project", NULL, NULL);
	if (window == NULL){
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	// Set up mouse input behaviour
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCursorPos(window, static_cast<double>(w / 2), static_cast<double>(h / 2));

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
	}
	glViewport(0, 0, w, h);

	scene = new Scene(w, h);
}

returnCode GameApp::mainLoop() {
	// Calculate frame time 
	currTime = static_cast<float>(glfwGetTime());
	float dTime = currTime - lastTime;
	lastTime = currTime;
	// Process the keyboard inputs 
	returnCode nextAction{ processInput() };
	glfwPollEvents();
	// Update the scene 
	scene->update(dTime);
	glfwSwapBuffers(window);

	return nextAction;
}

returnCode GameApp::processInput() {
	// Quit game if excape button is pushed 
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		return returnCode::QUIT;
	}
	int wasdState{ 0 };
	float walk_dir{ scene->player->eulers.z };
	bool walking{ false };

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		wasdState += 1;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		wasdState += 8;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		wasdState += 4;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		wasdState += 2;
	}

	switch (wasdState) {
	case 1:
	case 11:
		//walking forwards 
		walking = true;
		break;
	case 3:
		//left + forwards
		walking = true;
		walk_dir += 45;
		break;
	case 2:
	case 7:
		// left 
		walking = true;
		walk_dir += 90;
		break;
	case 6:
		//left + backwards 
		walking = true;
		walk_dir += 135;
		break;
	case 4:
	case 14:
		//backkwards 
		walking = true;
		walk_dir += 180;
		break;
	case 12:
		//right + backwards 
		walking = true;
		walk_dir += 225;
		break;
	case 8:
	case 13:
		//right 
		walking = true;
		walk_dir += 270;
		break;
	case 9:
		//right + forwards 
		walking = true;
		walk_dir += 315;
		break;

	}

	if (walking) {
		// Orientate walk direction with the players forward vector
		glm::vec3 forwards = glm::cos(glm::radians(walk_dir)) * scene->player->forwards;
		glm::vec3 sideways = glm::sin(glm::radians(walk_dir)) * glm::cross(scene->player->forwards, scene->player->up);

		scene->player->movePlayer(
			0.1f * frameTime / 16.0f * (forwards + sideways)
		);
	}

	double mouse_x, mouse_y;
	glfwGetCursorPos(window, &mouse_x, &mouse_y);
	glfwSetCursorPos(window, static_cast<double>(w / 2), static_cast<double>(h / 2));

	float delta_x{ static_cast<float>(mouse_x - static_cast<double>(w / 2)) };
	float delta_y{ static_cast<float>(mouse_y - static_cast<double>(h / 2)) };

	scene->player->spinPlayer(
		frameTime / 16.0f * glm::vec3{
			-delta_y, delta_x, 0.0f
		}
	);

	scene->player->updateVectors();

	return returnCode::CONTINUE;
}

GameApp::~GameApp() {

}