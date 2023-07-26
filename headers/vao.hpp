#pragma once
#ifndef VAO_HPP
#define VAO_HPP

#include <cassert>

#include "gl_object.hpp"

#include "gl_buffer_objects.hpp"

namespace skgl
{

class VAO : public GL_Object
{
public:

	// Data
	VBO m_vbo;
	EBO m_ebo;


	// Methods
	VAO();
	~VAO();

	void init(VBO vbo);
	void init(VBO vbo, EBO ebo);

	explicit VAO(VBO vbo) : VAO() { init(vbo); }
	VAO(VBO vbo, EBO ebo) : VAO() { init(vbo, ebo); }

	void bind() const;
	void unbind() const;

	void draw() const;

	void link(
		unsigned int index,
		int size = 3,
		unsigned int type = 0x1406,
		bool normalized = false,
		int stride = sizeof(Vertex),
		int offset_bytes = offsetof(Vertex, Vertex::m_pos)
	);

};

} //namespace skgl

#endif // !VAO_HPP
