#version 460 core

layout (location = 0) in vec3 aPos;   // per-vertex
layout (location = 1) in mat4 aModel; // per-instance, occupies locations 1-4
layout (location = 5) in vec3 aColor; // per-instance

out vec3 vColor;

void main() {
    gl_Position = aModel * vec4(aPos, 1.0);
    vColor = aColor;
}
