#pragma once
#ifndef MESH_HPP
#define MESH_HPP

#include <glm/glm.hpp>

#include "drawable.hpp"
#include "vao.hpp"
#include "material.hpp"

namespace skgl {

struct Mesh : public Drawable
{
	VAO m_vao;
	Material m_mat;
	glm::mat4 m_trans = glm::mat4(1.f);

	Mesh() {}

	Mesh(
		VAO vao,
		const Material& material = Material(),
		const glm::mat4& trans = glm::mat4(1.f)
	)	: m_vao(vao), m_mat(material), m_trans(trans) {}

	void draw(const Camera& camera, const Shader& shader) const override
	{
		shader.bind();

		m_mat.bind();

		shader.setMat4("model", m_trans);
		shader.setMat4("view", camera.look_at());
		shader.setMat4("proj", camera.get_proj());

		m_vao.draw();
	}
};



} // namespace skgl

#endif // !MESH_HPP
