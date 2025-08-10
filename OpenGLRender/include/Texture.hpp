// Texture.h
#pragma once
#include <glad/glad.h>
#include <string>

class Texture
{
public:
    GLuint id;
    std::string type;
    std::string path;
    Texture() = default;
    Texture(const std::string &path, const std::string &type);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    GLuint getID() const { return id; }
    std::string getType() const { return type; }
    std::string getPath() const { return path; }

private:
       void loadTexture();
};