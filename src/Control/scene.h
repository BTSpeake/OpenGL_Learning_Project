#include "../config.h"	
#include "../Models/player.h"
#include "../Utils/shader.h"	
#include "../Models/cube.h"	
#include "../Models/skybox.h"

class Scene {
public:
	Scene(int w, int h);
	~Scene();
	void update(float rate);
	Player* player;
private:
	unsigned int mainShader; 
	int w, h;
	Cube* cube;
	SkyBox* skybox;
};