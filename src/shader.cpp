#include "shader.hpp"

#include <glad/glad.h>

#include <iostream>

using namespace skgl;

void check_errors(unsigned int id, Shader::types type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != Shader::types::program)
    {
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(id, 1024, NULL, infoLog);
            throw std::runtime_error("ERROR::SHADER_PROGRAM_LINKING_ERROR\n" + std::string(infoLog));
        }
    }
    else
    {
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(id, 1024, NULL, infoLog);
            switch (type)
            {
            case skgl::Shader::types::vertex:
                throw std::runtime_error("ERROR::VERTEX_SHADER_COMPILATION_ERROR\n" + std::string(infoLog));
            case skgl::Shader::types::geometry:
                throw std::runtime_error("ERROR::GEOMETRY_SHADER_COMPILATION_ERROR\n" + std::string(infoLog));
            case skgl::Shader::types::fragment:
                throw std::runtime_error("ERROR::FRAGMENT_SHADER_COMPILATION_ERROR\n" + std::string(infoLog));

            default:
                throw std::runtime_error("ERROR::UNKNOWN_TYPE_SHADER_COMPILATION_ERROR\n" + std::string(infoLog));
            }
        }
    }
}


// SHADERS


void Shader::init(std::string_view code, types type)
{
    GLuint id;

    switch (type)
    {
    case skgl::Shader::types::vertex:
        id = glCreateShader(GL_VERTEX_SHADER);
        break;
    case skgl::Shader::types::geometry:
        id = glCreateShader(GL_GEOMETRY_SHADER);
        break;
    case skgl::Shader::types::fragment:
        id = glCreateShader(GL_FRAGMENT_SHADER);
        break;

    default:
        throw std::runtime_error("Unsupported shader type:");
    }

    if (id == 0)
        throw std::runtime_error("Couldn't create shader!");

    set_id(id);

    auto code_str = code.data();

    glShaderSource(*m_id, 1, &code_str, NULL);
    glCompileShader(*m_id);
    check_errors(*m_id, type);
}

void Shader::init(std::filesystem::path path, bool use_std_dir)
{
    auto fullpath = use_std_dir ? std_dir / path : path;

    std::ifstream vShaderFile(fullpath);

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    if (!vShaderFile.is_open())
        throw std::runtime_error("Could not open shader file located: " + fullpath.string());

    std::stringstream shader_stream;
    shader_stream << vShaderFile.rdbuf();

    Shader::types type;
    if      (fullpath.extension() == ".vert")
        type = Shader::types::vertex;

    else if (fullpath.extension() == ".geom")
        type = Shader::types::geometry;

    else if (fullpath.extension() == ".frag")
        type = Shader::types::fragment;

    else
        throw std::runtime_error("Unknown shader file extension " + fullpath.extension().string());
   
    init(shader_stream.str(), type);
}

Shader::Shader()
{
    skgl::log("Shader's constructor invoked");
    deleter = [](GLuint* ptr)
    {
        glDeleteShader(*ptr);
        delete ptr;
    };
}

Shader::~Shader()
{
    skgl::log("Shader's destructor invoked");
}



// PROGRAM

Program::Program()
{
    skgl::log("Program constructor invoked");
    deleter = [](GLuint* ptr)
    {
        glDeleteProgram(*ptr);
        delete ptr;
    };
}

Program::~Program()
{
    skgl::log("Program destructor invoked");
}

void Program::bind() const
{
    assert((*m_id) && "Tried to bind uninitialized shader program!\n");
    glUseProgram(*m_id);
}

void Program::unbind() const
{
    glUseProgram(*m_id);
}

void Program::init(Shader vert, Shader frag)
{
    auto id = glCreateProgram();
    set_id(id);

    glAttachShader(*m_id, *vert.m_id);
    glAttachShader(*m_id, *frag.m_id);

    glLinkProgram(*m_id);
    check_errors(*m_id, Shader::types::program);

    skgl::log("Shader successfully inited");
}

void Program::init(Shader vert, Shader geom, Shader frag)
{
    auto id = glCreateProgram();
    set_id(id);

    glAttachShader(*m_id, *vert.m_id);
    glAttachShader(*m_id, *geom.m_id);
    glAttachShader(*m_id, *frag.m_id);

    glLinkProgram(*m_id);
    check_errors(*m_id, Shader::types::program);

    skgl::log("Shader successfully inited");
}

// PROGRAM UNIFORM SETTERS


void Program::set_bool(std::string_view name, bool value) const
{
    glUniform1i(glGetUniformLocation(*m_id, name.data()), (int)value);
}
// ------------------------------------------------------------------------
void Program::set_int(std::string_view name, int value) const
{
    glUniform1i(glGetUniformLocation(*m_id, name.data()), value);
}
// ------------------------------------------------------------------------
void Program::set_float(std::string_view name, float value) const
{
    glUniform1f(glGetUniformLocation(*m_id, name.data()), value);
}
// ------------------------------------------------------------------------
void Program::set_vec(std::string_view name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(*m_id, name.data()), 1, &value[0]);
}
void Program::set_vec(std::string_view name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(*m_id, name.data()), x, y);
}
// ------------------------------------------------------------------------
void Program::set_vec(std::string_view name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(*m_id, name.data()), 1, &value[0]);
}
void Program::set_vec(std::string_view name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(*m_id, name.data()), x, y, z);
}
// ------------------------------------------------------------------------
void Program::set_vec(std::string_view name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(*m_id, name.data()), 1, &value[0]);
}
void Program::set_vec(std::string_view name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(*m_id, name.data()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Program::set_mat(std::string_view name, const glm::mat2& mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(*m_id, name.data()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Program::set_mat(std::string_view name, const glm::mat3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(*m_id, name.data()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Program::set_mat(std::string_view name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(*m_id, name.data()), 1, GL_FALSE, &mat[0][0]);
}