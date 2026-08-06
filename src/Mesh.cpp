#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Geometry/Mesh.hpp>
#include <Geometry/Vec3.hpp>
#include <Geometry/InstanceData.hpp>

Mesh::Mesh(const Vec3* verts, std::size_t count) : vertexCount{count} {
	// Create VBO + VAO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind VAO
	glBindVertexArray(VAO);

	// Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(Vec3), verts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), (void*)0);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::draw(std::size_t instanceCount) const {
	glBindVertexArray(VAO);
	glDrawArraysInstanced(GL_TRIANGLES, 0, vertexCount, static_cast<GLsizei>(instanceCount));
	glBindVertexArray(0);
}

void Mesh::setInstanceData(const InstanceData* data, std::size_t count) {
	glBindVertexArray(VAO);

	if (instanceVBO == 0) {
		glGenBuffers(1, &instanceVBO);
	}

	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(InstanceData), data, GL_STATIC_DRAW);

	std::size_t vec4Size = sizeof(Vec4);

	for (int i = 0; i < 4; ++i) {
		glVertexAttribPointer(
			1 + i, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceData),
			(void*)(offsetof(InstanceData, model) + i * vec4Size)
		);

		glEnableVertexAttribArray(1 + i);
		glVertexAttribDivisor(1 + i, 1); // advance once per instance, not per vertex
	}

	// color -> location 5
	glVertexAttribPointer(
		5, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceData),
		(void*)offsetof(InstanceData, color)
	);
	glEnableVertexAttribArray(5);
	glVertexAttribDivisor(5, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &instanceVBO);
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
