#pragma once 
#include "../config.h"
#include "scene.h"

enum class returnCode {
	CONTINUE, QUIT
};

class GameApp {
public:
	GameApp(int w, int h);
	~GameApp();
	returnCode mainLoop();
private:
	returnCode processInput();
	//void calculateFrameRate();

	GLFWwindow* window;
	int w, h;
	Scene* scene; 
	double lastTime, currTime;
	int nFrames;
	float frameTime;
};