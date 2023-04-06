#pragma once 
#include "../config.h"
#include "scene.h"
#include "../Utils/shader.h"
#include "../Model/SkyBox.h"


struct LightLoc {
	std::array<unsigned int, 3> colLoc, posLoc, strLoc;
};

class Engine {
public:
	Engine(int w, int h);
	~Engine();
	void render(Scene* scene);

	unsigned int shader;
	unsigned int camPosLoc;
	unsigned int viewLoc; 
	unsigned int modelLoc;
	LightLoc lights;
	SkyBox skyBox;
	
};