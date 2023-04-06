#pragma once
#include "../config.h"
#include "../Scene/scene.h"

class SkyBox {
public:
	SkyBox();
	~SkyBox();
	void render(Scene* scene);
	unsigned int textureID;
	unsigned int shader;
private:
	void loadCubeMap();
	void createSkyBoxCube();
	unsigned int VBO, VAO, nVerts;
};
