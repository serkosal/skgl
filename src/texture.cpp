#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace skgl
{

std::filesystem::path Texture::standart_dir = "resources/textures/";

void Texture::init(const std::filesystem::path& path, bool flip, bool use_standart_dir)
{
    if (m_id)
        Texture::deleter(m_id.get());

    set_id(0);

    glGenTextures(1, m_id.get());
    glBindTexture(GL_TEXTURE_2D, *m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    auto result_path = use_standart_dir ? standart_dir / path : path;


    unsigned char* data = stbi_load(result_path.string().data(), &width, &height, &nrChannels, 0);
    if (data)
    {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }
    else
    {
        stbi_image_free(data);
        throw std::runtime_error("Error to load texture located: " + result_path.string());
    }
}

} //namespace skgl