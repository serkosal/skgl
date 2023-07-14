#pragma once
#ifndef MESH_HPP
#define MESH_HPP

#include "drawable.hpp"
#include "texture.hpp"

namespace skgl {

struct Mesh : public Drawable
{
	Texture m_texture;

	Mesh(
		Shader shader, 
		VAO vao,
		Texture texture,
		const glm::mat4& trans = glm::mat4(1.f)
	)	: m_shader(shader), m_vao(vao), m_texture(texture) {}

	void draw(const Camera& camera) override
	{
		m_shader.bind();

		m_shader.setMat4("model", m_trans);
		m_shader.setMat4("view", camera.look_at());
		m_shader.setMat4("proj", camera.get_proj());

		m_texture.bind();

		m_vao.draw();
	}
};



} // namespace skgl

#endif // !MESH_HPP
