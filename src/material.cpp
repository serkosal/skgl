#include "material.hpp"

#include <glad/glad.h>

using namespace skgl;

void Material::bind() const
{
	if (m_diffuse)
	{
		glActiveTexture(GL_TEXTURE0);
		m_diffuse.bind();
	}
	if (m_specular)
	{
		glActiveTexture(GL_TEXTURE1);
		m_specular.bind();
	}
}