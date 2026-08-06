#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Geometry/Vec3.hpp>
#include <Geometry/InstanceData.hpp>

class Mesh {
public:
	Mesh(const Vec3 *verts, std::size_t count);
	~Mesh();

	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;

	Mesh(Mesh&& other) noexcept;
	Mesh& operator=(Mesh&& other) noexcept;

	void setInstanceData(const InstanceData* data, std::size_t count);
	void draw(std::size_t instanceCount) const;

private:
	GLuint VAO{0};
	GLuint VBO{0};
	GLuint instanceVBO{0};
	std::size_t vertexCount{0};
};
