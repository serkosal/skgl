#include "model.hpp"

#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace skgl;

void Model::init(
	const std::filesystem::path& filename, 
	bool flipUV,
	bool use_standart_dir)
{
	skgl::log("Model's init() called");

	Assimp::Importer importer;

	int post_process = aiProcess_Triangulate | aiProcess_OptimizeMeshes |
		aiProcess_OptimizeGraph | aiProcess_GenNormals;
	post_process |= flipUV ? aiProcess_FlipUVs : 0;

	auto result_path = use_standart_dir ? standart_dir / filename : filename;
	std::string res_path_str = std::filesystem::absolute(result_path).string();

	const aiScene* scene = importer.ReadFile(res_path_str, post_process);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::string msg = "Couldn't load the model's file located" + res_path_str;
		skgl::log(msg);
		throw std::runtime_error(msg);
	}

	const aiNode* rootNode = scene->mRootNode;
	process_node(rootNode, scene);
}

inline glm::mat4 to_glm_mat(const aiMatrix4x4& mat)
{
	return glm::mat4(
		mat.a1, mat.a2, mat.a3, mat.a4,
		mat.b1, mat.b2, mat.b3, mat.b4,
		mat.c1, mat.c2, mat.c3, mat.c4,
		mat.d1, mat.d2, mat.d3, mat.d4
	);
}

void Model::process_node(const aiNode* node, const aiScene* scene, const glm::mat4& trans)
{
	for (size_t meshNum = 0; meshNum < node->mNumMeshes; ++meshNum)
		process_mesh(scene->mMeshes[node->mMeshes[meshNum]], scene, trans);

	for (size_t childNum = 0; childNum < node->mNumChildren; ++childNum)
		process_node(node->mChildren[childNum], scene, glm::mat4(1.f));
}

void skgl::Model::process_mesh(const aiMesh* mesh, const aiScene* scene, const glm::mat4& trans)
{
	std::vector<Vertex> vertices;
	vertices.reserve(mesh->mNumVertices);
	for (size_t i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex vert;


		vert.m_pos = {
			mesh->mVertices[i].x,
			mesh->mVertices[i].y,
			mesh->mVertices[i].z
		};


		if (mesh->HasNormals())
			vert.m_nor = {
				mesh->mNormals[i].x,
				mesh->mNormals[i].y,
				mesh->mNormals[i].z,
			};


		//checks if mesh has texture coords
		if (mesh->mTextureCoords[0])
			vert.m_tex = {
				mesh->mTextureCoords[0][i].x,
				mesh->mTextureCoords[0][i].y,
			};

		vertices.push_back(vert);
	}

	std::vector<GLuint> indices;
	indices.reserve(mesh->mNumFaces * 3ULL);

	for (size_t i = 0; i < mesh->mNumFaces; ++i)
	{
		indices.push_back(mesh->mFaces[i].mIndices[0]);
		indices.push_back(mesh->mFaces[i].mIndices[1]);
		indices.push_back(mesh->mFaces[i].mIndices[2]);
	}


	m_meshes.push_back(
		Mesh(VAO(VBO(vertices), EBO(indices)), Texture())
	);

	m_meshes.back().m_vao.bind();
	m_meshes.back().m_vao.m_vbo.bind();
	m_meshes.back().m_vao.m_ebo.bind();

	m_meshes.back().m_vao.link(
		0, 3, GL_FLOAT, false,
		sizeof(skgl::Vertex),
		offsetof(skgl::Vertex, skgl::Vertex::m_pos)
	);

	
	m_meshes.back().m_vao.link(
		1, 3, GL_FLOAT, false,
		sizeof(skgl::Vertex),
		offsetof(skgl::Vertex, skgl::Vertex::m_nor)
	);
	

	/*
	m_meshes.back().m_vao.link(
		1, 2, GL_FLOAT, false,
		sizeof(skgl::Vertex),
		offsetof(skgl::Vertex, skgl::Vertex::m_tex)
	);
	*/
}
