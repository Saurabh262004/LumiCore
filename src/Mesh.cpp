#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <Mesh.hpp>
#include <Vertex.hpp>
#include <vector>

Mesh::Mesh(const Vertex* verts, std::size_t count) : vertexCount{count} {
	// Create VBO + VAO

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind the VAO first
	glBindVertexArray(VAO);

	std::cout << vertexCount << '\n';

	// Bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(
		GL_ARRAY_BUFFER,
		count * sizeof(Vertex),
		verts,
		GL_STATIC_DRAW
	);

	// Tell OpenGL how the vertex data is laid out
	glVertexAttribPointer(
		0,					// location
		3,					// x y z
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),		// stride
		(void*)0			// offset
	);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Mesh::draw() {
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glBindVertexArray(0);
}
