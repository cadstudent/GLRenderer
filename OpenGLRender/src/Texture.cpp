// Texture.cpp
#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include <iostream>
#define DEBUG
Texture::Texture(const std::string &path, const std::string &type)
    : path(path), type(type)
{
    loadTexture();
}

Texture::~Texture()
{
    glDeleteTextures(1, &id);
}

void Texture::loadTexture()
{
    GLuint id;
    this->id = id;
    glGenTextures(1, &id);
#ifdef DEBUG
    std::cout << "Texture type: " << type << std::endl;
    std::cout << "Texture id: " << id << std::endl;
#endif
    int width, height, nrComponents;
    //stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);

    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
#ifdef DEBUG
        std::cout << "Texture loaded successfully at path: " << path << std::endl;
#endif
    }
    else
    {
        std::cerr << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }
}

void Texture::bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id);
}