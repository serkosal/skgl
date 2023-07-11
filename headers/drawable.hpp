#pragma once
#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <glm/glm.hpp>

#include "shader.hpp"
#include "vao.hpp"

namespace skgl 
{

struct Drawable
{
	// Data
	Shader m_shader;
	VAO m_vao;

	glm::mat4 m_trans = glm::mat4(1.f);

	// Methods

	Drawable(Shader shader, VAO vao)
		: m_shader(shader), m_vao(vao) {}

	virtual void draw() 
	{
		m_shader.bind();
		m_vao.draw();
	}
};

} // namespace skgl

#endif // !DRAWABLE_HPP
