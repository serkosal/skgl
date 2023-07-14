#pragma once
#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
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
    static std::filesystem::path standart_dir;


    // Methods

    Shader() 
    { 
        deleter = [](GLuint* ptr)
        {
            glDeleteProgram(*ptr);
            delete ptr;
        };
    }


    void init(const std::filesystem::path& path, bool use_standart_dir = true);


    explicit Shader(const std::filesystem::path& path, bool use_standart_dir = true)
        : Shader() 
    { 
        init(path, use_standart_dir); 
    }


    void bind() { glUseProgram(*m_id); }
    void unbind() { glUseProgram(*m_id); }

    //uniform setters
    void setBool(std::string_view name, bool value) const
    {
        glUniform1i(glGetUniformLocation(*m_id, name.data()), (int)value);
    }
    // ------------------------------------------------------------------------
    void setInt(std::string_view name, int value) const
    {
        glUniform1i(glGetUniformLocation(*m_id, name.data()), value);
    }
    // ------------------------------------------------------------------------
    void setFloat(std::string_view name, float value) const
    {
        glUniform1f(glGetUniformLocation(*m_id, name.data()), value);
    }
    // ------------------------------------------------------------------------
    void setVec2(std::string_view name, const glm::vec2& value) const
    {
        glUniform2fv(glGetUniformLocation(*m_id, name.data()), 1, &value[0]);
    }
    void setVec2(std::string_view name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(*m_id, name.data()), x, y);
    }
    // ------------------------------------------------------------------------
    void setVec3(std::string_view name, const glm::vec3& value) const
    {
        glUniform3fv(glGetUniformLocation(*m_id, name.data()), 1, &value[0]);
    }
    void setVec3(std::string_view name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(*m_id, name.data()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void setVec4(std::string_view name, const glm::vec4& value) const
    {
        glUniform4fv(glGetUniformLocation(*m_id, name.data()), 1, &value[0]);
    }
    void setVec4(std::string_view name, float x, float y, float z, float w) const
    {
        glUniform4f(glGetUniformLocation(*m_id, name.data()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void setMat2(std::string_view name, const glm::mat2& mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(*m_id, name.data()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat3(std::string_view name, const glm::mat3& mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(*m_id, name.data()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat4(std::string_view name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(*m_id, name.data()), 1, GL_FALSE, &mat[0][0]);
    }
private:
    void check_errors(GLuint id, std::string type) const;
};

} //namespace skgl

#endif // !SHADER_HPP
