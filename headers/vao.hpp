#pragma once
#ifndef VAO_HPP
#define VAO_HPP

#include "gl_object.hpp"

#include "vbo.hpp"
#include "ebo.hpp"

namespace skgl
{

class VAO : public GL_Object
{
public:
	VBO vbo;
	EBO ebo;

	VAO()
	{
		deleter = [](GLuint* ptr)
		{
			glDeleteVertexArrays(1, ptr);
			delete ptr;
		};
	}

	void init(VBO vbo)
	{
		this->vbo = vbo;

		if (_id)
			deleter(_id.get());
		set_id(0);

		glGenVertexArrays(1, _id.get());
	}
	void init(VBO vbo, EBO ebo)
	{
		this->vbo = vbo;
		this->ebo = ebo;

		if (_id)
			deleter(_id.get());
		set_id(0);

		glGenVertexArrays(1, _id.get());
	}

	VAO(VBO vbo) : VAO() { init(vbo); }
	VAO(VBO vbo, EBO ebo) : VAO() { init(vbo, ebo); }

	void bind() { glBindVertexArray(*_id); }
	void unbind() { glBindVertexArray(0); }

	void draw()
	{
		bind();
		vbo.bind();

		if (ebo._id)
		{
			ebo.bind();
			glDrawElements(GL_TRIANGLES, ebo.get_size(), GL_UNSIGNED_INT, 0);
		}
		else
			glDrawArrays(GL_TRIANGLES, 0, vbo.get_size());
	}

	void link(
		GLuint index,
		GLint size = 3,
		GLenum type = GL_FLOAT,
		bool normalized = false,
		GLsizei stride = sizeof(Vertex),
		GLsizei offset_bytes = offsetof(Vertex, Vertex::_pos)
	)
	{
		bind();
		vbo.bind();
		if (ebo._id)
			ebo.bind();

		glVertexAttribPointer(index, size, type, normalized, stride, (void*)(offset_bytes));
		glEnableVertexAttribArray(index);
	}

};

} //namespace skgl

#endif // !VAO_HPP
