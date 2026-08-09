#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <Geometry/Vec.hpp>

struct Vertex {
	Vec3 position;
	Vec3 normal;
};

struct VertexAttribute {
	GLuint location;
	GLuint componentCount;
	std::size_t offset;
};

struct VertexLayout {
	std::size_t stride;
	std::vector<VertexAttribute> attributes;
};
