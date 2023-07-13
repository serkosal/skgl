#pragma once
#ifndef MAIN_HPP
#define MAIN_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "window.hpp"

#include "shader.hpp"
#include "texture.hpp"

#include "vbo.hpp"
#include "ebo.hpp"
#include "vao.hpp"

#include "camera.hpp"
#include "drawable.hpp"


const std::vector<skgl::Vertex> vertices =
{
	{ {  0.5f,  0.5f, 0.0f }, /**/ {1.f, 1.f } }, // top right
	{ {  0.5f, -0.5f, 0.0f }, /**/ {1.f, 0.f } }, // bottom right
	{ { -0.5f, -0.5f, 0.0f }, /**/ {0.f, 0.f } }, // bottom left
	{ { -0.5f,  0.5f, 0.0f }, /**/ {0.0, 1.f } }  // top left 
};

const std::vector<GLuint> indices = {  // note that we start from 0!
	0, 1, 3,  // first Triangle
	1, 2, 3   // second Triangle
};


#endif // !MAIN_HPP
