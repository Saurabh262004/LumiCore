#version 460 core

in vec3 vColor;
in vec3 vNormal;

uniform vec3 lightDir;

out vec4 FragColor;

void main() {
	vec3 N = normalize(vNormal);
	float diff = max(dot(N, -lightDir), 0.0);

	float ambient = 0.15;
	vec3 result = vColor * (ambient + diff * (1.0 - ambient));

	FragColor = vec4(result, 1.0);
}
