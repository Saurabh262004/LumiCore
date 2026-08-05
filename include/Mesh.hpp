#ifndef MESH_HPP
#define MESH_HPP

#include <Vertex.hpp>

class Mesh {
public:
	Mesh(const Vertex *verts, std::size_t count);
	~Mesh();
	void draw();

private:
	GLuint VAO{};
	GLuint VBO{};
	std::size_t vertexCount{};
};

#endif
