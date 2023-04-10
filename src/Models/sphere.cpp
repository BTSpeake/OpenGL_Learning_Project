#include "sphere.h"

Sphere::Sphere(SphereCreateInfo* createInfo) {
	this->pos = createInfo->pos;

	// Make a reflective shader program 
	shader = util::load_shader(
		"Resources/Shaders/reflection.vs", "Resources/Shaders/reflection.fs"
	);


	std::vector<float> vertices = util::load_model_from_file(
		createInfo->objPath, createInfo->preT
	);

	createVAO(vertices);
}

void Sphere::createVAO(std::vector<float> vertices) {
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

void Sphere::setProjection(glm::mat4 projM) {
	glUseProgram(shader);
	glUniformMatrix4fv(glGetUniformLocation(shader, "proj"), 1, GL_FALSE, glm::value_ptr(projM));
}

void Sphere::setView(glm::mat4 viewM) {
	glUseProgram(shader);
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(viewM));
}

void Sphere::setCameraPosition(glm::vec3 position) {
	glUseProgram(shader);
	glUniform3fv(glGetUniformLocation(shader, "camPos"), 1, glm::value_ptr(position));
}

void Sphere::render(unsigned int textureID) {
	glUseProgram(shader);
	glBindTextureUnit(GL_TEXTURE_CUBE_MAP, textureID);
	glm::mat4 modelM{ glm::mat4(1.0f) };
	modelM = glm::translate(modelM, pos);
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, nVerts);
}

Sphere::~Sphere() {
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}
