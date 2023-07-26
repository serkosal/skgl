#include "vao.hpp"

#include <glad/glad.h>

#include <cassert>

using namespace skgl;

VAO::VAO()
{
	skgl::log("VAO's constructor invoked");
	deleter = [](GLuint* ptr)
	{
		glDeleteVertexArrays(1, ptr);
		delete ptr;
	};
}

VAO::~VAO()
{
	skgl::log("VAO's destructor invoked");
}

void VAO::init(VBO vbo)
{
	skgl::log("VAO's init() called");
	m_vbo = vbo;

	if (m_id)
		deleter(m_id.get());
	set_id(0);

	glGenVertexArrays(1, m_id.get());
	skgl::log("VAO is successfully inited");
}
void VAO::init(VBO vbo, EBO ebo)
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

void VAO::bind() const
{
	assert((*m_id) && "Tried to bind uninitialized Vertex Array Object (VAO) !\n");
	glBindVertexArray(*m_id);
}
void VAO::unbind() const { glBindVertexArray(0); }

void VAO::draw() const
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

void VAO::link(
	unsigned int index,
	int size,
	unsigned int type,
	bool normalized,
	int stride,
	int offset_bytes
)
{
	bind();
	m_vbo.bind();
	if (m_ebo.m_id)
		m_ebo.bind();

	glVertexAttribPointer(index, size, type, normalized, stride, (void*)(offset_bytes));
	glEnableVertexAttribArray(index);
}