#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Geometry/Mat.hpp>

class Shader {
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);

	~Shader();

	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;

	Shader(Shader&& other) noexcept;
	Shader& operator=(Shader&& other) noexcept;

	void setVec3(const std::string& name, const Vec3& vec) const;
	void setMat4(const std::string& name, const Mat4& mat) const;

	void use() const;

private:
	GLuint program{};
};
