#pragma once
#ifndef VBO_HPP
#define VBO_HPP

#include <cassert>
#include <vector>

#include "gl_object.hpp"
#include "vertex.hpp"

namespace skgl
{

class VAO;

class VBO : public GL_Object
{
	friend class VAO;


	// Data
	size_t m_verticies_n = 0;

public:

	// Methods
	VBO()
	{
		skgl::log("VBO constructor invoked");
		deleter = [](GLuint* ptr)
		{
			glDeleteBuffers(1, ptr);
			delete ptr;
		};
	}

	void init(const std::vector<Vertex>& vertices, GLenum usage = GL_STATIC_DRAW)
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

	explicit VBO(const std::vector<Vertex>& vertices, GLenum usage = GL_STATIC_DRAW)
		: VBO()
	{ init(vertices, usage); }

	size_t get_vert_num() { return m_verticies_n; }

	void bind() 
	{ 
		assert( (*m_id) && "Tried to bind uninitialized Vertex Buffer Object (VBO) !\n");
		glBindBuffer(GL_ARRAY_BUFFER, *m_id); 
	}
	void unbind() 
	{ 
		glBindBuffer(GL_ARRAY_BUFFER, 0);  
	}

	~VBO()
	{
		skgl::log("VBO's destructor invoked");
	}
};

} //namespace skgl

#endif // !VBO_HPP
