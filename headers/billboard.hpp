#pragma once
#ifndef BILLBOARD_HPP
#define BILLBOARD_HPP

#include <cmath>

#include <glm/glm.hpp>

#include "camera.hpp"
#include "drawable.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "vao.hpp"

namespace skgl {

struct Billboard : public Drawable
{
	VAO m_vao;
	Texture m_texture;

	glm::vec3 m_pos{0.f};
	glm::vec2 m_size{1.f};

	mutable float a = 0.f;


	void draw(const Camera& camera, const Shader& shader) const override
	{
		glm::vec3 d_pos = m_pos - camera.m_pos;

		if (d_pos.length() > FLT_EPSILON || -d_pos.length() < FLT_EPSILON)
			a = atan2(d_pos.z, d_pos.x) - 3.1415926535897932385 / 2.0;

		glm::mat4 model = glm::scale(glm::mat4(1.f), { m_size.x, m_size.y, 1.f });
		model = glm::rotate(model, -a, { 0.f, 1.f, 0.f });
		model = glm::translate(model, m_pos);


		shader.bind();

		shader.setMat4("model", model);
		shader.setMat4("view", camera.look_at());
		shader.setMat4("proj", camera.get_proj());

		m_texture.bind();

		m_vao.draw();
	}

	Billboard()
	{
		m_vao = VAO(

			VBO(std::vector<skgl::Vertex>{
				{ {  0.5f, 0.5f, 0.0f }, /**/{ 0.f, 0.f, 1.f }, /**/{ 1.f, 1.f } }, // top right
				{ {  0.5f, -0.5f, 0.0f }, /**/ {0.f, 0.f, 1.f}, /**/ {1.f, 0.f } }, // bottom right
				{ { -0.5f, -0.5f, 0.0f }, /**/ {0.f, 0.f, 1.f}, /**/ {0.f, 0.f } }, // bottom left
				{ { -0.5f,  0.5f, 0.0f }, /**/ {0.f, 0.f, 1.f}, /**/ {0.0, 1.f } }  // top left 
			}),

			EBO(std::vector<GLuint>{
				0, 1, 3,
				1, 2, 3
			})
		);
	}
};

}  // namespace skgl

#endif