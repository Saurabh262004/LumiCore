#version 460 core

layout (location = 0) in vec3 pos;   // per-vertex
layout (location = 1) in mat4 model; // per-instance, occupies locations 1-4
layout (location = 5) in vec3 color; // per-instance

uniform mat4 viewProjection; // view * projection matrix from camera

out vec3 vColor;

void main() {
    gl_Position = viewProjection * model * vec4(pos, 1.0);
    vColor = color;
}
