#pragma once
#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/glm.hpp>

#include "shader.hpp"

namespace skgl {

struct Light
{
	glm::vec3 m_pos = glm::vec3(0.f);
	glm::vec3 m_color = glm::vec3(1.f);

	Light() {}
	Light(const glm::vec3& pos, const glm::vec3& color)
		: m_pos(pos), m_color(color) {}

	void apply(const Program& program) const
	{
		program.bind();

		program.set_vec("lightPos", m_pos);
		program.set_vec("lightColor", m_color);
	}
};

} // namespace skgl

#endif // !LIGHT_HPP
