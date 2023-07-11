#pragma once
#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm/glm.hpp>

namespace skgl
{

struct Vertex
{
	Vertex() {}

	Vertex(const glm::vec3& pos, const glm::vec2& tex)
		: _pos(pos), _tex(tex) {}

	glm::vec3 _pos = glm::vec3(0.f); //float * 3 12
	glm::vec2 _tex = glm::vec2(0.f); //float * 2 8
};

} // namespace skgl

#endif // !VERTEX_HPP
