#pragma once
#ifndef SHADER_HPP
#define SHADER_HPP

#include <glm/glm.hpp>

#include <filesystem>
#include <fstream>
#include <string_view>

#include "gl_object.hpp"

namespace skgl
{

class Program;

struct Shader : public GL_Object
{
    friend class Program;

    inline static std::filesystem::path std_dir = "resources/shaders/";

    enum class types
    {
        vertex,
        geometry,
        fragment,

        program,
    };

    Shader();
    Shader(std::string_view code, types type)
    {
        init(code, type);
    }
    Shader(std::filesystem::path path, bool use_std_dir = true)
    {
        init(path, use_std_dir);
    }

    void init(std::string_view code, types type);
    void init(std::filesystem::path path, bool use_std_dir = true);

    ~Shader();
};

struct Program : public GL_Object
{
public:
    // Methods

    Program();

    void init(Shader vert,              Shader frag);
    void init(Shader vert, Shader geom, Shader frag);

    Program(Shader vert,              Shader frag)
    {   
        init(vert, frag); 
    }
    Program(Shader vert, Shader geom, Shader frag)
    {   
        init(vert, geom, frag); 
    }

    ~Program();

    void bind() const;
    void unbind() const;

    //uniform setters
    void set_bool(std::string_view name, bool value) const;
    void set_int(std::string_view name, int value) const;
    void set_float(std::string_view name, float value) const;

    void set_vec(std::string_view name, const glm::vec2& value) const;
    void set_vec(std::string_view name, float x, float y) const;
    void set_vec(std::string_view name, const glm::vec3& value) const;
    void set_vec(std::string_view name, float x, float y, float z) const;
    void set_vec(std::string_view name, const glm::vec4& value) const;
    void set_vec(std::string_view name, float x, float y, float z, float w) const;

    void set_mat(std::string_view name, const glm::mat2& mat) const;
    void set_mat(std::string_view name, const glm::mat3& mat) const;
    void set_mat(std::string_view name, const glm::mat4& mat) const;
};

} //namespace skgl

#endif // !SHADER_HPP
