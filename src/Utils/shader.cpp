#include "shader.h"

unsigned int util::load_shader(const char* vfPth, const char* ffPth) {
	int success;
	char errLog[1024];

	std::ifstream fileReader;
	std::stringstream bufferedLines;
	std::string line;

	// Read in vertex shader
	fileReader.open(vfPth);
	while (std::getline(fileReader, line)) {
		bufferedLines << line << '\n';
	}

	std::string vSstr = bufferedLines.str();
	const char* vSsrc = vSstr.c_str();
	bufferedLines.str("");
	fileReader.close();

	// Read in fragment shader 
	fileReader.open(ffPth);
	while (std::getline(fileReader, line)) {
		bufferedLines << line << '\n';
	}
	std::string fSstr = bufferedLines.str();
	const char* fSsrc = fSstr.c_str();
	bufferedLines.str("");
	fileReader.close();

	// Create Vertex shader 
	unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vSsrc, NULL);
	glCompileShader(vShader);
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vShader, 1024, NULL, errLog);
		std::cout << "Vertex shader compilation error\n";
		std::cout << "Error associated with file: " << vfPth << '\n';
		std::cout << errLog << "\n";
	}

	// Create fragment shader 
	unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fSsrc, NULL);
	glCompileShader(fShader);
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fShader, 1024, NULL, errLog);
		std::cout << "Fragment shader compilation error\n";
		std::cout << "Error associated with file: " << ffPth << '\n';
		std::cout << errLog << "\n";
	}

	// Link shaders 
	unsigned int shader = glCreateProgram();
	glAttachShader(shader, vShader);
	glAttachShader(shader, fShader);
	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader, 1024, NULL, errLog);
		std::cout << "Shader program linking error\n" << errLog << "\n";
	}

	// Clean up redundant individual shaders 
	glDeleteShader(vShader);
	glDeleteShader(fShader);

	return shader;
}