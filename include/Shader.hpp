#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Geometry/Mat4.hpp>

class Shader {
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);

	~Shader();

	void setMat4(const std::string& name, const Mat4& mat) const;

	void use() const;

private:
	GLuint program{};
};

#endif