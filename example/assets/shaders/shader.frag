#version 460 core

in vec3 vColor;
in vec3 vNormal;
in vec2 vTexCoord;

struct Material {
	vec3 color;
	sampler2D diffuse;
	int hasTexture;
};

uniform Material material;
uniform vec3 lightDir;

out vec4 FragColor;

void main() {
	vec3 albedo = vColor * material.color;

	if (material.hasTexture == 1) {
		albedo *= texture(material.diffuse, vTexCoord).rgb;
	}

	vec3 N = normalize(vNormal);
	float diff = max(dot(N, -lightDir), 0.0);

	float ambient = 0.15;
	vec3 result = albedo * (ambient + diff * (1.0 - ambient));

	FragColor = vec4(result, 1.0);
}
