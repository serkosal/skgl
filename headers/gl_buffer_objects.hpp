#pragma once
#ifndef GL_BUFFER_OBJECTS_HPP
#define GL_BUFFER_OBJECTS_HPP


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
	VBO();

	// implement enum that copies and default value 
	// GL_STATIC_DRAW = 0x88E4
	void init(const std::vector<Vertex>& vertices, unsigned int usage = 0x88E4);

	explicit VBO(const std::vector<Vertex>& vertices, unsigned int usage = 0x88E4)
		: VBO()
	{
		init(vertices, usage);
	}

	size_t get_vert_num() const { return m_verticies_n; }

	void bind() const;
	void unbind() const;

	~VBO()
	{
		skgl::log("VBO's destructor invoked");
	}
};

class EBO : public GL_Object
{
	friend class VAO;

	// DATA
	size_t m_indices_n = 0;

public:
	// Methods
	EBO();

	~EBO();

	void bind() const;
	void unbind() const;

	size_t get_ind_num() const { return m_indices_n; }

	void init(const std::vector<unsigned int>& indices, unsigned int usage = 0x88E4);

	explicit EBO(const std::vector<unsigned int>& indices, unsigned int usage = 0x88E4)
		: EBO() {
		init(indices, usage);
	}
};

} //namespace skgl

#endif // !GL_BUFFER_OBJECTS_HPP
