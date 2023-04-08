#pragma once 
#include "../config.h"
#include "../Utils/obj_loader.h"
#include "../Utils/image_loader.h"	

struct CubeCreateInfo {
	glm::vec3 pos, eulers;
	//unsigned int shader;
	glm::mat4 preT; 
};

class Cube {
public:
	Cube(CubeCreateInfo* createInfo);
	~Cube();
	void update(float rate);
	void render(unsigned int shader);
	glm::vec3 pos, eulers;
private:
	unsigned int VAO, VBO, nVerts, textureID;
	void createVAO(std::vector<float> vertices);
	void createTexture();
};