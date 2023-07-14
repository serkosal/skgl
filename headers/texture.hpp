#pragma once
#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <cassert>
#include <filesystem>

#include <glad/glad.h>

#include "gl_object.hpp"

namespace skgl
{

class Texture : public GL_Object
{
public:

    // Static data
    inline static std::filesystem::path standart_dir = "resources/textures/";


    // Methods

    Texture()
    {
        deleter = [](GLuint* ptr)
        {
            glDeleteTextures(1, ptr);
            delete ptr;
        };
    }
    
    void init(
        const std::filesystem::path& path,
        bool flip = true,
        bool use_standart_dir = true
    );

    explicit Texture(
        const std::filesystem::path& path,
        bool flip = true,
        bool use_standart_dir = true
    ) : Texture()
    {
        init(path, flip, use_standart_dir);
    }

    void bind() const 
    { 
        assert((*m_id) && "Tried to bind uninitialized texture!\n");
        glBindTexture(GL_TEXTURE_2D, *m_id); 
    }
    void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }
};

} //namespace skgl

#endif // !TEXTURE_HPP
