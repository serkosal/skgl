#pragma once
#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <glm/glm.hpp>

#include "shader.hpp"
#include "vao.hpp"
#include "camera.hpp"

namespace skgl 
{

struct Drawable
{
	virtual void draw(const Camera& camera, const Program& program) const = 0;
};

} // namespace skgl

#endif // !DRAWABLE_HPP
