#include "shader.hpp"

namespace skgl
{

std::filesystem::path Shader::standart_dir = "resources/shaders/";

void Shader::init(const std::filesystem::path& path, bool use_standart_dir)
{
    if (m_id)
        Shader::deleter(m_id.get());

    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    auto vertex_path = use_standart_dir ? standart_dir / path : path;
    auto fragment_path = vertex_path;

    vShaderFile.open(vertex_path.concat(".vs").string());
    fShaderFile.open(fragment_path.concat(".fs").string());

    std::stringstream vShaderStream, fShaderStream;
    // read file's buffer contents into streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    // close file handlers
    vShaderFile.close();
    fShaderFile.close();
    // convert stream into string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    check_errors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    check_errors(fragment, "FRAGMENT");

    auto id = glCreateProgram();
    set_id(id);

    glAttachShader(*m_id, vertex);
    glAttachShader(*m_id, fragment);
    glLinkProgram(*m_id);
    check_errors(*m_id, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}


void Shader::check_errors(GLuint id, std::string type) const
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(id, 1024, NULL, infoLog);
            throw std::runtime_error("ERROR::SHADER_COMPILATION_ERROR of type: " + type + "\n" + infoLog);
        }
    }
    else
    {
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(id, 1024, NULL, infoLog);
            throw std::runtime_error("ERROR::PROGRAM_LINKING_ERROR of type: " + type + "\n" + infoLog);
        }
    }
}


} //namespace skgl