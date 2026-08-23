#pragma once

#include <string>
#include <unordered_map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <GLib/Geometry/Vec.hpp>
#include <GLib/Geometry/Mat.hpp>
#include <GLib/Geometry/Mat.hpp>

class Shader {
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);

	void addVec2Uniform(std::string id, Vec2 vec);
	void addVec3Uniform(std::string id, Vec3 vec);
	void addVec4Uniform(std::string id, Vec4 vec);
	void addMat4Uniform(std::string id, Mat4 mat);

	void uploadUniforms();

	~Shader();

	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;

	Shader(Shader&& other) noexcept;
	Shader& operator=(Shader&& other) noexcept;

	void setVec2(const std::string& name, const Vec2& vec) const;
	void setVec3(const std::string& name, const Vec3& vec) const;
	void setVec4(const std::string& name, const Vec4& vec) const;
	void setMat4(const std::string& name, const Mat4& mat) const;

	void use() const;

private:
	GLuint program{};

	std::unordered_map<std::string, Vec2> vec2Uniforms;
	std::unordered_map<std::string, Vec3> vec3Uniforms;
	std::unordered_map<std::string, Vec4> vec4Uniforms;
	std::unordered_map<std::string, Mat4> mat4Uniforms;
};
