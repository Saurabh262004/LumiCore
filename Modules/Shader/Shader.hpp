#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include "../../external/glad/glad.h"
#include <GLFW/glfw3.h>

class Shader {
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);

	~Shader();

	void use() const;

private:
	GLuint program;
};

#endif