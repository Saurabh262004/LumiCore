#version 460 core

layout (location = 0) in vec3 pos;      // per-vertex, from VertexLayout
layout (location = 1) in mat4 model;    // per-instance, locations 1-4
layout (location = 5) in vec3 color;    // per-instance
layout (location = 6) in vec3 normal;   // per-vertex, from VertexLayout

uniform mat4 viewProjection;

out vec3 vColor;
out vec3 vNormal;

void main() {
	gl_Position = viewProjection * model * vec4(pos, 1.0);
	vColor = color;
	vNormal = mat3(model) * normal; // rotate normal into world space
}
