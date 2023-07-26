#pragma once
#ifndef SHAPES_HPP
#define SHAPES_HPP

#include "vao.hpp"

namespace skgl {

struct Shapes
{
	static const VAO& Quad()
	{
		if (m_quad_is_created == false)
			create_quad();
		return m_quad_vao;
	}

private:
	inline static VAO m_quad_vao = VAO();
	inline static bool m_quad_is_created = false;

	static void create_quad();
};
	

} // namespace skgl

#endif // !SHAPES_HPP