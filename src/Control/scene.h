#include "../config.h"	
#include "../Models/player.h"
#include "../Utils/shader.h"	
#include "../Models/cube.h"	
#include "../Models/sphere.h"
#include "../Models/skybox.h"
#include "../Models/light.h"

class Scene {
public:
	Scene(int w, int h);
	~Scene();
	void update(float rate);
	Player* player;
private:
	unsigned int mainShader, reflectShader; 
	int w, h;
	Cube* cube;
	Sphere* sphere;
	SkyBox* skybox;
	Light* light;
};