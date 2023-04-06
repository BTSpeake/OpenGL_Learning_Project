#include "SkyBox.h"
#include "../Utils/image_loader.h"
#include "../Utils/shader.h"

SkyBox::SkyBox() {
	loadCubeMap();
	shader = util::load_shader("Resources/Shaders/vertex_skybox.txt", "Resources/Shaders/frag_skybox.txt");
	createSkyBoxCube();
}

void SkyBox::render(Scene* scene) {
	// Render the skybox
	
	glDepthMask(GL_FALSE);
	glUseProgram(shader);

	// set the view matrix 
	glm::mat4 look{
		glm::lookAt(
			scene->player->position,
			scene->player->position + scene->player->forwards,
			scene->player->up
		)
	};
	glm::mat4 viewM = glm::mat4(glm::mat3(look));
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(viewM));

	// draw
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
	// Re-enable depth writing
	glDepthMask(GL_TRUE);

}

void SkyBox::loadCubeMap() {
	// Load the images for each face of the cube in the skybox
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	
	// Cooordinate system is flipped so +z is upwards, 
	std::vector<std::string> faces {
		"Resources/Textures/skybox/right.jpg",
		"Resources/Textures/skybox/left.jpg",
		"Resources/Textures/skybox/top.jpg",
		"Resources/Textures/skybox/bottom.jpg",
		"Resources/Textures/skybox/back.jpg",
		"Resources/Textures/skybox/front.jpg"
	};

	for (unsigned int i = 0; i < 6; i++) {
		image img = util::load_image_from_file(faces[i].c_str(), 0);
		if (*img.pixels) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, img.w, img.h, 0, GL_RGB, GL_UNSIGNED_BYTE, img.pixels);
		}
		else {
			std::cout << "Cubemap texture failed to load from file: " << faces[i] << '\n';
		}
		util::free_image_mem(img);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}

void SkyBox::createSkyBoxCube() {
	// Create the cube that will be used to render the skybox
	float vertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	nVerts = 36;
	glCreateBuffers(1, &VBO);
	glCreateVertexArrays(1, &VAO);
	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, 3 * sizeof(float));
	glNamedBufferStorage(VBO, 36 * 3 * sizeof(float), vertices, GL_DYNAMIC_STORAGE_BIT);
	glEnableVertexArrayAttrib(VAO, 0);
	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(VAO, 0, 0);

}

SkyBox::~SkyBox() {
	// Clean up memory usage
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}