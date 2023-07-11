#pragma once
#ifndef VBO_HPP
#define VBO_HPP

#include <vector>

#include "gl_object.hpp"
#include "vertex.hpp"

namespace skgl
{

class VAO;

class VBO : public GL_Object
{
	size_t _size = 0;
	friend class VAO;
public:
	VBO()
	{
		deleter = [](GLuint* ptr)
		{
			glDeleteBuffers(1, ptr);
			delete ptr;
		};
	}

	void init(const std::vector<Vertex>& vertices, GLenum usage = GL_STATIC_DRAW)
	{
		_size = vertices.size();

		if (_id)
			deleter(_id.get());
		set_id(0);

		glGenBuffers(1, _id.get());
		bind();

		glBufferData(GL_ARRAY_BUFFER, _size * sizeof(Vertex), vertices.data(), usage);
	}

	VBO(const std::vector<Vertex>& vertices, GLenum usage = GL_STATIC_DRAW)
		: VBO()
	{ init(vertices, usage); }

	size_t get_size() { return _size; }

	void bind() { glBindBuffer(GL_ARRAY_BUFFER, *_id); }
	void unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0);  }
};

} //namespace skgl

#endif // !VBO_HPP
