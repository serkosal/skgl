#pragma once
#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <glm/glm.hpp>

#include "shader.hpp"
#include "vao.hpp"
#include "camera.hpp"

namespace skgl 
{

struct Drawable
{
	// Data
	Shader m_shader;
	VAO m_vao;

	glm::mat4 m_trans = glm::mat4(1.f);

	// Methods

	Drawable() 
	{
		skgl::log("Drawable's constructor invoked");
	}

	~Drawable()
	{
		skgl::log("Drawable's destructor invoked");
	}

	Drawable(Shader shader, VAO vao)
		: m_shader(shader), m_vao(vao) {}

	virtual void draw(const Camera& camera)
	{
		m_shader.bind();

		m_shader.setMat4("model", m_trans);
		m_shader.setMat4("view", camera.look_at());
		m_shader.setMat4("proj", camera.get_proj());

		m_vao.draw();
	}
};

} // namespace skgl

#endif // !DRAWABLE_HPP
