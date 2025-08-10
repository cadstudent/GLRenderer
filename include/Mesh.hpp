// Mesh.h
#pragma once
#include <glad/glad.h>
#include "Vertex.hpp"
#include "Texture.hpp"
#include <vector>

class Mesh
{
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
         std::vector<Texture> textures);
    ~Mesh();

    void draw(GLuint shaderProgram);
    void CoutInfo();

private:
    void setupMesh();

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    GLuint VAO, VBO, EBO;
};