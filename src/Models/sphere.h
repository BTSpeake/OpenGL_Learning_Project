#pragma once
#include "../config.h"
#include "../Utils/obj_loader.h"
#include "../Utils/shader.h"
#include "../Utils/image_loader.h"

struct SphereCreateInfo {
	glm::vec3 pos, eulers;
	glm::mat4 preT;
	const char* objPath;
};

class Sphere {
public:
	Sphere(SphereCreateInfo* createInfo);
	~Sphere();
	void render(unsigned int textureID);
	void setProjection(glm::mat4 projM);
	void setView(glm::mat4 viewM);
	void setCameraPosition(glm::vec3 position);
	glm::vec3 pos;
private:
	unsigned int shader, VAO, VBO, nVerts;
	void createVAO(std::vector<float> vertices);
};