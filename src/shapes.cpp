#include "shapes.hpp"

#include <glad/glad.h>

using namespace skgl;

void Shapes::create_quad()
{
	m_quad_vao.init(
		VBO({
			{ {  0.5f,  0.5f, 0.0f }, /**/ {0.f, 0.f, 1.f}, /**/ {1.f, 1.f } }, // top right
			{ {  0.5f, -0.5f, 0.0f }, /**/ {0.f, 0.f, 1.f}, /**/ {1.f, 0.f } }, // bottom right
			{ { -0.5f, -0.5f, 0.0f }, /**/ {0.f, 0.f, 1.f}, /**/ {0.f, 0.f } }, // bottom left
			{ { -0.5f,  0.5f, 0.0f }, /**/ {0.f, 0.f, 1.f}, /**/ {0.0, 1.f } }  // top left
			}),
		EBO({
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
			})
	);

	m_quad_vao.link(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, Vertex::m_pos));
	m_quad_vao.link(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, Vertex::m_nor));
	m_quad_vao.link(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, Vertex::m_tex));

	m_quad_is_created = true;
}
