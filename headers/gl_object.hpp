#pragma once
#ifndef GL_OBJECT_HPP
#define GL_OBJECT_HPP

#include <memory>

#define SK_LOGGING
#include "log.hpp"

namespace skgl
{

class GL_Object
{
private:
	using SKuint = unsigned int;
public:

	// Constuctors

	operator bool() const { return bool(m_id); }

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
	std::shared_ptr<SKuint> m_id;


	// Methods
	void (*deleter)(SKuint* ptr) = [](SKuint* ptr)
	{
		delete ptr;
	};

	void set_id(unsigned int id)
	{
		m_id = std::shared_ptr<SKuint>(new SKuint(id), deleter);
	}


};

} //namespace skgl

#endif // !GL_OBJECT_HPP
