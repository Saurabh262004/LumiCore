#include <iostream>

#include <Shader.hpp>
#include <Util.hpp>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
	// compile shaders
	std::string vertexCode = Util::readFile(vertexPath);
	const char* vertexSource = vertexCode.c_str();

	std::string fragmentCode = Util::readFile(fragmentPath);
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);

	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);

	glCompileShader(fragmentShader);

	// Link Program
	program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	// Shaders are no longer needed after linking
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader() {
	std::cout << "Deleting shader\n";
	glDeleteProgram(program);
}

void Shader::setVec3(const std::string& name, const Vec3& vec) const {
    GLint location = glGetUniformLocation(program, name.c_str());
    glUniform3f(location, vec.x, vec.y, vec.z);
}

void Shader::setMat4(const std::string& name, const Mat4& mat) const {
	GLint location = glGetUniformLocation(program, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, mat.data());
}

void Shader::use() const {
	glUseProgram(program);
}
