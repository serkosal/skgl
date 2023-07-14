//Elements buffer object is the collection of edges of the figure

#pragma once
#ifndef EBO_HPP
#define EBO_HPP

#include <cassert>
#include <vector>

#include "gl_object.hpp"

namespace skgl
{

class VAO;

class EBO : public GL_Object
{
	friend class VAO;


	// DATA
	size_t m_indices_n = 0;

public:

	// Methods
	EBO()
	{
		skgl::log("EBO's constructor invoked");

		deleter = [](GLuint* ptr)
		{
			glDeleteBuffers(1, ptr);
			delete ptr;
		};
	}

	~EBO()
	{
		skgl::log("EBO's destructor invoked");
	}

	void bind() 
	{
		assert((*m_id) && "Tried to bind uninitialized Element buffer object (EBO) !\n");
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *m_id); 
	}
	void unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

	size_t get_ind_num() { return m_indices_n; }

	void init(const std::vector<GLuint>& indices, GLenum usage = GL_STATIC_DRAW)
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

	explicit EBO(const std::vector<GLuint>& indices, GLenum usage = GL_STATIC_DRAW)
		: EBO() { init(indices, usage); }
};

} //namespace skgl

#endif // !EBO_HPP
