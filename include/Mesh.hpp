#ifndef MESH_HPP
#define MESH_HPP

#include <Vertex.hpp>
#include <vector>

class Mesh {
public:
	Mesh(const Vertex *verts, std::size_t count);
	~Mesh();
	void use();

private:
    std::vector<Vertex> vertices;
	GLuint VAO;
	GLuint VBO;
};

#endif
