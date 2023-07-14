#pragma once
#ifndef GL_OBJECT_HPP
#define GL_OBJECT_HPP

#include <memory>

#include <glad/glad.h>

#define SK_LOGGING
#include "log.hpp"

namespace skgl
{

class GL_Object
{
public:

	// Constuctors

	GL_Object() 
	{
		skgl::log("GL_Object constructor invoked");
	}
	~GL_Object() 
	{
		skgl::log("GL_Object destructor invoked");
	};
protected:

	// Data
	std::shared_ptr<GLuint> m_id;


	// Methods
	void (*deleter)(GLuint* ptr) = [](GLuint* ptr)
	{
		delete ptr;
	};

	void set_id(GLuint id)
	{
		m_id = std::shared_ptr<GLuint>(new GLuint(id), deleter);
	}


};

} //namespace skgl

#endif // !GL_OBJECT_HPP
