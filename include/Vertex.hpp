// Vertex.h
#pragma once
#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 Position; // 顶点位置
    glm::vec3 Normal = glm::vec3(0.0f);
    glm::vec2 TexCoords = glm::vec2(0.0f);
    glm::vec3 Tangent = glm::vec3(0.0f);
    glm::vec3 Bitangent = glm::vec3(0.0f);
};