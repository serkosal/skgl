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

	explicit Drawable(VAO vao)
		: m_vao(vao) {}

	virtual void draw(const Camera& camera, const Shader& shader) const
	{
		shader.bind();

		shader.setMat4("model", m_trans);
		shader.setMat4("view", camera.look_at());
		shader.setMat4("proj", camera.get_proj());

		m_vao.draw();
	}
};

} // namespace skgl

#endif // !DRAWABLE_HPP
