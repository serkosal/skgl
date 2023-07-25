#pragma once
#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "texture.hpp"

namespace skgl {

struct Material
{
	Texture m_diffuse;
	Texture m_specular;

	Material() {}

	Material(Texture diffuse, Texture specular)
		: m_diffuse(diffuse), m_specular(specular)
	{}

	void bind() const
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
};

} // namespace skgl

#endif // !MATERIAL_HPP
