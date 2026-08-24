#include <iostream>
#include <utility>

#include <lumi/Shader.hpp>
#include <lumi/Util.hpp>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
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

	program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader() {
	std::cout << "Deleting shader\n";
	glDeleteProgram(program);
}

void Shader::addVec2Uniform(std::string id, Vec2 vec) {	vec2Uniforms[id] = vec; }
void Shader::addVec3Uniform(std::string id, Vec3 vec) {	vec3Uniforms[id] = vec; }
void Shader::addVec4Uniform(std::string id, Vec4 vec) {	vec4Uniforms[id] = vec; }
void Shader::addMat4Uniform(std::string id, Mat4 mat) {	mat4Uniforms[id] = mat; }
void Shader::addIntUniform(std::string id, int value) {	intUniforms[id] = value; }

void Shader::setVec2(const std::string& name, const Vec2& vec) const {
	GLint location = glGetUniformLocation(program, name.c_str());
	glUniform2f(location, vec.x, vec.y);
}

void Shader::setVec3(const std::string& name, const Vec3& vec) const {
	GLint location = glGetUniformLocation(program, name.c_str());
	glUniform3f(location, vec.x, vec.y, vec.z);
}

void Shader::setVec4(const std::string& name, const Vec4& vec) const {
	GLint location = glGetUniformLocation(program, name.c_str());
	glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
}

void Shader::setMat4(const std::string& name, const Mat4& mat) const {
	GLint location = glGetUniformLocation(program, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, mat.data());
}

void Shader::setInt(const std::string& name, int value) const {
	GLint location = glGetUniformLocation(program, name.c_str());
	glUniform1i(location, value);
}

void Shader::uploadUniforms() {
	for (auto& [id, vec2] : vec2Uniforms) setVec2(id, vec2);
	for (auto& [id, vec3] : vec3Uniforms) setVec3(id, vec3);
	for (auto& [id, vec4] : vec4Uniforms) setVec4(id, vec4);
	for (auto& [id, mat4] : mat4Uniforms) setMat4(id, mat4);
	for (auto& [id, value] : intUniforms) setInt(id, value);
}

void Shader::use() const {
	glUseProgram(program);
}

Shader::Shader(Shader&& other) noexcept :
	program{std::exchange(other.program, 0)},
	vec2Uniforms{std::move(other.vec2Uniforms)},
	vec3Uniforms{std::move(other.vec3Uniforms)},
	vec4Uniforms{std::move(other.vec4Uniforms)},
	mat4Uniforms{std::move(other.mat4Uniforms)},
	intUniforms{std::move(other.intUniforms)}
{}

Shader& Shader::operator=(Shader&& other) noexcept {
	if (this != &other) {
		if (program != 0) glDeleteProgram(program);

		program = std::exchange(other.program, 0);
		vec2Uniforms = std::move(other.vec2Uniforms);
		vec3Uniforms = std::move(other.vec3Uniforms);
		vec4Uniforms = std::move(other.vec4Uniforms);
		mat4Uniforms = std::move(other.mat4Uniforms);
		intUniforms = std::move(other.intUniforms);
	}

	return *this;
}
