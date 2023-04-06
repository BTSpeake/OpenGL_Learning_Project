#pragma once 
#include "../config.h"

struct CubeCreateInfo {
	glm::vec3 pos, eulers;
	unsigned int shader;
	//const char* fname; 
	glm::mat4 preT;
};

class Cube {
public:
	glm::vec3 pos, eulers;
	Cube(CubeCreateInfo* createInfo);
	~Cube();
	void update(float rate);
	void render(unsigned int shdaer);
private: 
	unsigned int VAO, VBO, nVerts, textureID;
	void createVAO(std::vector<float> vertices);
	void createTexture();
};