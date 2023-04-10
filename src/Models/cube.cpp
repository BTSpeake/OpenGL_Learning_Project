#include "cube.h"

Cube::Cube(CubeCreateInfo* createInfo) {
	this->pos = createInfo->pos;
	this->eulers = createInfo->eulers;

	std::vector<float> vertices = util::load_model_from_file(
		createInfo->objPath, createInfo->preT
	);

	createVAO(vertices);
	createTexture(createInfo->texPath);
}

void Cube::createVAO(std::vector<float> vertices) {
	// Create the VAO and VBO objects for the cube object 

	nVerts = vertices.size() / 8;
	//std::cout << "Cube vertices: " << nVerts << '\n';
	glCreateBuffers(1, &VBO);
	glCreateVertexArrays(1, &VAO);
	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, 8 * sizeof(float));
	glNamedBufferStorage(VBO, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_STORAGE_BIT);

	// Vertex coordinates
	glEnableVertexArrayAttrib(VAO, 0);
	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(VAO, 0, 0);

	// Texture coordinates 
	glEnableVertexArrayAttrib(VAO, 1);
	glVertexArrayAttribFormat(VAO, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
	glVertexArrayAttribBinding(VAO, 1, 0);

	// Normal vectors 
	glEnableVertexArrayAttrib(VAO, 2);
	glVertexArrayAttribFormat(VAO, 2, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float));
	glVertexArrayAttribBinding(VAO, 2, 0);
}

void Cube::createTexture(const char* texPath) {
	int w, h;
	//image material = util::load_image_from_file("Resources/Textures/wood.jpg", 4);
	image material = util::load_image_from_file(texPath, 4);
	w = material.w;
	h = material.h;
	unsigned char* data = material.pixels;
	glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
	glTextureStorage2D(textureID, 1, GL_RGBA8, w, h);
	glTextureSubImage2D(textureID, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTextureParameteri(textureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(textureID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(textureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(textureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	util::free_image_memory(material);
}

void Cube::update(float rate) {
	eulers.x += 0.0001 * rate;
	if (eulers.x > 360) {
		eulers.x -= 360;
	}
	eulers.y += 0.0002 * rate;
	if (eulers.y > 360) {
		eulers.y -= 360;
	}
}

void Cube::render(unsigned int shader) {

	glEnable(GL_CULL_FACE);

	// Activate the correct shader and texture
	glUseProgram(shader);
	glBindTextureUnit(0, textureID);
	// Update the model matrix
	glm::mat4 modelM{ glm::mat4(1.0f) };
	modelM = glm::translate(modelM, pos);
	modelM = modelM * glm::eulerAngleXYZ(eulers.x, eulers.y, eulers.z);
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	// Load the VAO and draw the object
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, nVerts);
}

Cube::~Cube() {
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteTextures(1, &textureID);
}

