// Model.hpp
#pragma once
#include <string>
#include <vector>
#include <Geometry/Mesh.hpp>

struct aiNode;
struct aiScene;
struct aiMesh;

class Model {
public:
	explicit Model(const std::string& path);

	Model(const Model&) = delete;
	Model& operator=(const Model&) = delete;
	Model(Model&&) noexcept = default;
	Model& operator=(Model&&) noexcept = default;

	void draw(std::size_t instanceCount) const;
	void setInstanceData(const InstanceData* data, std::size_t count);
	void updateInstanceData(const InstanceData* data, std::size_t count);

private:
	std::vector<Mesh> meshes;

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};
