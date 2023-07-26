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

	void bind() const;
};

} // namespace skgl

#endif // !MATERIAL_HPP
