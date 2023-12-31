#pragma once
#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <filesystem>

#include "gl_object.hpp"

namespace skgl
{

class Texture : public GL_Object
{
public:

    // Static data
    inline static std::filesystem::path standart_dir = "resources/textures/";


    // Methods

    Texture();
    
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

    void bind() const;
    void unbind() const;
};

} //namespace skgl

#endif // !TEXTURE_HPP
