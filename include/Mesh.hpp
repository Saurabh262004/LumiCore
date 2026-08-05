#ifndef MESH_HPP
#define MESH_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Vec3.h>
#include <Vertex.hpp>

class Mesh {
public:
	Mesh(const Vertex *verts, std::size_t count);
	~Mesh();

	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;

	Mesh(Mesh&& other) noexcept;
	Mesh& operator=(Mesh&& other) noexcept;

	void setInstanceOffsets(const Vec3 *offsets, std::size_t count);
	void draw() const;
	void drawInstanced(std::size_t instanceCount) const;

private:
	GLuint VAO{0};
	GLuint VBO{0};
	GLuint instanceVBO{0};
	std::size_t vertexCount{0};
};

#endif
