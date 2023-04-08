#pragma once 
#include "../config.h"
#include "../Utils/shader.h"
#include "../Utils/image_loader.h"

class SkyBox {
public:
	SkyBox();
	~SkyBox();
	void render(glm::mat4 viewM);
	unsigned int shader;
private:
	void loadCubemap(std::vector<std::string> faces);
	unsigned int VAO, VBO, textureID;
};