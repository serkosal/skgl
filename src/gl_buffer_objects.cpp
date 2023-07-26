#include "gl_buffer_objects.hpp"

#include <glad/glad.h>

#include <cassert>


using namespace skgl;

VBO::VBO()
{
	skgl::log("VBO constructor invoked");
	deleter = [](GLuint* ptr)
	{
		glDeleteBuffers(1, ptr);
		delete ptr;
	};
}

void VBO::init(const std::vector<Vertex>& vertices, unsigned int usage)
{
	skgl::log("VBO init called");
	m_verticies_n = vertices.size();

	if (m_id)
		deleter(m_id.get());
	set_id(0);

	glGenBuffers(1, m_id.get());
	bind();

	glBufferData(GL_ARRAY_BUFFER, m_verticies_n * sizeof(Vertex), vertices.data(), usage);
}

void VBO::bind() const
{
	assert((*m_id) && "Tried to bind uninitialized Vertex Buffer Object (VBO) !\n");
	glBindBuffer(GL_ARRAY_BUFFER, *m_id);
}
void VBO::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

EBO::EBO()
{
	skgl::log("EBO's constructor invoked");

	deleter = [](GLuint* ptr)
	{
		glDeleteBuffers(1, ptr);
		delete ptr;
	};
}

EBO::~EBO()
{
	skgl::log("EBO's destructor invoked");
}

void EBO::bind() const
{
	assert((*m_id) && "Tried to bind uninitialized Element buffer object (EBO) !\n");
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *m_id);
}
void EBO::unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

void EBO::init(const std::vector<unsigned int>& indices, unsigned int usage)
{
	skgl::log("EBO's init() called");

	m_indices_n = indices.size();

	if (m_id)
		deleter(m_id.get());
	set_id(0);
	glGenBuffers(1, m_id.get());

	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices_n * sizeof(GLuint), indices.data(), usage);
}