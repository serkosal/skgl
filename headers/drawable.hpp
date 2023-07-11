#pragma once
#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <glm/glm.hpp>

#include "shader.hpp"
#include "vao.hpp"

namespace skgl 
{

struct Drawable
{
	Shader shader;
	VAO vao;
	glm::mat4 trans = glm::mat4(1.f);

	Drawable(Shader shader, VAO vao)
		: shader(shader), vao(vao) {}

	virtual void draw() 
	{
		shader.bind();
		vao.draw();
	}
};

} // namespace skgl

#endif // !DRAWABLE_HPP
