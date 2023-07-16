#pragma once
#ifndef VAO_HPP
#define VAO_HPP

#include <cassert>

#include "gl_object.hpp"

#include "vbo.hpp"
#include "ebo.hpp"

namespace skgl
{

class VAO : public GL_Object
{
public:

	// Data
	VBO m_vbo;
	EBO m_ebo;


	// Methods
	VAO()
	{
		skgl::log("VAO's constructor invoked");
		deleter = [](GLuint* ptr)
		{
			glDeleteVertexArrays(1, ptr);
			delete ptr;
		};
	}
	~VAO()
	{
		skgl::log("VAO's destructor invoked");
	}

	void init(VBO vbo)
	{
		skgl::log("VAO's init() called");
		m_vbo = vbo;

		if (m_id)
			deleter(m_id.get());
		set_id(0);

		glGenVertexArrays(1, m_id.get());
		skgl::log("VAO is successfully inited");
	}
	void init(VBO vbo, EBO ebo)
	{
		skgl::log("VAO's init() called");
		m_vbo = vbo;
		m_ebo = ebo;

		if (m_id)
			deleter(m_id.get());
		set_id(0);

		glGenVertexArrays(1, m_id.get());
		skgl::log("VAO is successfully inited");
	}

	explicit VAO(VBO vbo) : VAO() { init(vbo); }
	VAO(VBO vbo, EBO ebo) : VAO() { init(vbo, ebo); }

	void bind() const
	{
		assert((*m_id) && "Tried to bind uninitialized Vertex Array Object (VAO) !\n");
		glBindVertexArray(*m_id); 
	}
	void unbind() const { glBindVertexArray(0); }

	void draw() const
	{
		bind();
		m_vbo.bind();

		if (m_ebo.m_id)
		{
			m_ebo.bind();
			glDrawElements(GL_TRIANGLES, m_ebo.get_ind_num(), GL_UNSIGNED_INT, 0);
		}
		else
			glDrawArrays(GL_TRIANGLES, 0, m_vbo.get_vert_num());
	}

	void link(
		GLuint index,
		GLint size = 3,
		GLenum type = GL_FLOAT,
		bool normalized = false,
		GLsizei stride = sizeof(Vertex),
		GLsizei offset_bytes = offsetof(Vertex, Vertex::m_pos)
	)
	{
		bind();
		m_vbo.bind();
		if (m_ebo.m_id)
			m_ebo.bind();

		glVertexAttribPointer(index, size, type, normalized, stride, (void*)(offset_bytes));
		glEnableVertexAttribArray(index);
	}

};

} //namespace skgl

#endif // !VAO_HPP
