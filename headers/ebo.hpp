//Elements buffer object is the collection of edges of the figure

#pragma once
#ifndef EBO_HPP
#define EBO_HPP

#include <vector>

#include "gl_object.hpp"

namespace skgl
{

class VAO;

class EBO : public GL_Object
{
	friend class VAO;
	size_t _size = 0;
public:
	EBO()
	{
		deleter = [](GLuint* ptr)
		{
			glDeleteBuffers(1, ptr);
			delete ptr;
		};
	}

	void bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *_id); }
	void unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

	size_t get_size() { return _size; }

	void init(const std::vector<GLuint>& indices, GLenum usage = GL_STATIC_DRAW)
	{
		_size = indices.size();

		if (_id)
			deleter(_id.get());
		set_id(0);
		glGenBuffers(1, _id.get());

		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _size * sizeof(GLuint), indices.data(), usage);
	}

	EBO(const std::vector<GLuint>& indices, GLenum usage = GL_STATIC_DRAW)
		: EBO() { init(indices, usage); }
};

} //namespace skgl

#endif // !EBO_HPP
