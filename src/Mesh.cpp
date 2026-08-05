#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <Mesh.hpp>
#include <Vec3.h>
#include <Vertex.hpp>
#include <vector>

Mesh::Mesh(const Vertex* verts, std::size_t count) : vertexCount{count} {
	// Create VBO + VAO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind VAO
	glBindVertexArray(VAO);

	// Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(Vertex), verts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &instanceVBO);
}

void Mesh::draw() const {
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glBindVertexArray(0);
}

void Mesh::setInstanceOffsets(const Vec3* offsets, std::size_t count) {
	glBindVertexArray(VAO);

	if (instanceVBO == 0) {
		glGenBuffers(1, &instanceVBO);
	}

	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(Vec3), offsets, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribDivisor(1, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::drawInstanced(std::size_t instanceCount) const {
	glBindVertexArray(VAO);
	glDrawArraysInstanced(GL_TRIANGLES, 0, vertexCount, static_cast<GLsizei>(instanceCount));
	glBindVertexArray(0);
}

Mesh::Mesh(Mesh&& other) noexcept : VAO{other.VAO}, VBO{other.VBO}, vertexCount{other.vertexCount} {
	other.VAO = 0;
	other.VBO = 0;
	other.vertexCount = 0;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept {
	if (this != &other) {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);

		VAO = other.VAO;
		VBO = other.VBO;
		vertexCount = other.vertexCount;

		other.VAO = 0;
		other.VBO = 0;
		other.vertexCount = 0;
	}

	return *this;
}
