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

class Shader : public GL_Object
{
public:

    // Static data
    inline static std::filesystem::path standart_dir = "resources/shaders/";


    // Methods

    Shader();

    ~Shader();


    void init(const std::filesystem::path& path, bool use_standart_dir = true);


    explicit Shader(const std::filesystem::path& path, bool use_standart_dir = true)
        : Shader() 
    { 
        init(path, use_standart_dir); 
    }


    void bind() const;
    void unbind() const;

    //uniform setters
    void setBool(std::string_view name, bool value) const;
    void setInt(std::string_view name, int value) const;
    void setFloat(std::string_view name, float value) const;
    void setVec2(std::string_view name, const glm::vec2& value) const;
    void setVec2(std::string_view name, float x, float y) const;
    void setVec3(std::string_view name, const glm::vec3& value) const;
    void setVec3(std::string_view name, float x, float y, float z) const;
    void setVec4(std::string_view name, const glm::vec4& value) const;
    void setVec4(std::string_view name, float x, float y, float z, float w) const;
    void setMat2(std::string_view name, const glm::mat2& mat) const;
    void setMat3(std::string_view name, const glm::mat3& mat) const;
    void setMat4(std::string_view name, const glm::mat4& mat) const;
private:
    void check_errors(unsigned int id, std::string type) const;
};

} //namespace skgl

#endif // !SHADER_HPP
