//#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Geometry/Model.hpp>
#include <Geometry/Vertex.hpp>
#include <stdexcept>

Model::Model(const std::string& path) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_PreTransformVertices);

	if (!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !scene->mRootNode) {
		throw std::runtime_error("Assimp error: " + std::string(importer.GetErrorString()));
	}

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene) {
	for (unsigned i = 0; i < node->mNumMeshes; ++i) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	for (unsigned i = 0; i < node->mNumChildren; ++i) {
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<Vertex> vertices;
	vertices.reserve(mesh->mNumVertices);

	for (unsigned i = 0; i < mesh->mNumVertices; ++i) {
		Vertex v{};
		v.position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
		if (mesh->HasNormals())
			v.normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
		v.texCoord = mesh->mTextureCoords[0]
			? Vec2{ mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y }
			: Vec2{ 0.0f, 0.0f };
		vertices.push_back(v);
	}

	std::vector<std::uint32_t> indices;
	indices.reserve(mesh->mNumFaces * 3);
	for (unsigned i = 0; i < mesh->mNumFaces; ++i) {
		const aiFace& face = mesh->mFaces[i];
		for (unsigned j = 0; j < face.mNumIndices; ++j)
			indices.push_back(face.mIndices[j]);
	}

	//std::cout << "Mesh: " << vertices.size() << " verts, " << indices.size() << " indices\n";
	//std::cout << "Has vertex colors: " << mesh->HasVertexColors(0) << '\n';

	return Mesh(vertices.data(), vertices.size(), indices.data(), indices.size(), Vertex::layout());
}

void Model::draw(std::size_t instanceCount) const {
	for (const auto& mesh : meshes) mesh.draw(instanceCount);
}

void Model::setInstanceData(const InstanceData* data, std::size_t count) {
	for (auto& mesh : meshes) mesh.setInstanceData(data, count);
}

void Model::updateInstanceData(const InstanceData* data, std::size_t count) {
	for (auto& mesh : meshes) mesh.updateInstanceData(data, count);
}
