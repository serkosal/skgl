#pragma once
#ifndef GL_OBJECT_HPP
#define GL_OBJECT_HPP

#include <memory>

#include <glad/glad.h>

namespace skgl
{

class GL_Object
{
public:
	GL_Object() {}
	~GL_Object() {};
protected:
	void (*deleter)(GLuint* ptr) = [](GLuint* ptr)
	{
		delete ptr;
	};

	void set_id(GLuint id)
	{
		_id = std::shared_ptr<GLuint>(new GLuint(id), deleter);
	}

	std::shared_ptr<GLuint> _id;
};

} //namespace skgl

#endif // !GL_OBJECT_HPP
