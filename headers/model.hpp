#pragma once
#ifndef MODEL_HPP
#define MODEL_HPP

#include "drawable.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "log.hpp"
#include "camera.hpp"

#include <assimp/scene.h>

#include <filesystem>
#include <vector>

namespace skgl {

class Model : public Drawable
{
public:

	// Data

	inline static std::filesystem::path standart_dir = "resources/models/";

	std::vector<Mesh> m_meshes;

	// Methods

	Model() 
	{
		skgl::log("Model's constructor invoked");
	}

	void init(
		const std::filesystem::path& filename,
		bool flipUV = false, 
		bool use_standart_dir = true
	);

	explicit Model(
		const std::filesystem::path& filename,
		bool flipUV = false, 
		bool use_standart_dir = true
	)	: Model()
	{
		init(filename);
	}

	void draw(const Camera& camera, const Shader& shader) const override
	{
		shader.bind();

		shader.setMat4("view", camera.look_at());
		shader.setMat4("proj", camera.get_proj());
		shader.setVec3("viewPos", camera.m_pos);

		for (const auto& el : m_meshes)
		{
			shader.setMat4("model", el.m_trans);
			el.m_vao.draw();
		}
	}

	~Model() 
	{
		skgl::log("Model's destructor invoked");
	}

private:
	void process_node(const aiNode* node, const aiScene* scene, const glm::mat4& trans = glm::mat4(1.f));
	void process_mesh(const aiMesh* mesh, const aiScene* scene, const glm::mat4& trans = glm::mat4(1.f));
};

} // namespace skgl

#endif // !MODEL_HPP
