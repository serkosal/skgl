#pragma once
#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm/glm.hpp>

namespace skgl
{

struct Vertex
{

	// Data
	glm::vec3 m_pos;
	glm::vec2 m_tex;

	// Methods

	Vertex(
		const glm::vec3& pos = glm::vec3(0.f),
		const glm::vec2& tex = glm::vec2(0.f))
	: m_pos(pos), m_tex(tex) {}
};

} // namespace skgl

#endif // !VERTEX_HPP
