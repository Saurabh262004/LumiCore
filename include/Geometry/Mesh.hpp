#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdint>

#include <Geometry/Vec.hpp>
#include <Geometry/Mat.hpp>
#include <Geometry/Vertex.hpp>

struct InstanceData {
	Mat4 model; // position + rotation + scale
	Vec3 color;
};

class Mesh {
public:
	Mesh(const void* vertexData, std::size_t vertexCount, const VertexLayout& layout);
	Mesh(const void* vertexData, std::size_t vertexCount, const std::uint32_t* indices, std::size_t indexCount, const VertexLayout& layout);
	//Mesh(const Vec3 *verts, std::size_t count);
	~Mesh();

	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;

	Mesh(Mesh&& other) noexcept;
	Mesh& operator=(Mesh&& other) noexcept;

	void setInstanceData(const InstanceData* data, std::size_t count);
	void updateInstanceData(const InstanceData* data, std::size_t count);
	void draw(std::size_t instanceCount) const;

private:
	GLuint VAO{0};
	GLuint VBO{0};
	GLuint EBO{0};
	GLuint instanceVBO{0};
	GLuint instanceBaseLocation{1};
	std::size_t vertexCount{0};
	std::size_t indexCount{0};
};
