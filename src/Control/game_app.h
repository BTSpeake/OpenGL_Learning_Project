#pragma once 
#include "../config.h"
#include "../Scene/scene.h"
#include "../Scene/engine.h"

enum class returnCode {
	CONTINUE, QUIT
};

class GameApp {
public:
	GameApp(int w, int h);
	~GameApp();
	returnCode mainLoop();
private:
	GLFWwindow* makeWindow();
	returnCode processInput();
	void calculateFrameRate();

	GLFWwindow* window;
	int w, h;
	Scene* scene;
	Engine* renderer;

	double lastTime, currTime; 
	int nFrames; 
	float frameTime; 
};