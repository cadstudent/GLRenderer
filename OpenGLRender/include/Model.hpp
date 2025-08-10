// Model.h
#pragma once

#include <glad/glad.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <vector>
#include <map>
#include "Mesh.hpp"
#include "Texture.hpp"

class Model
{
public:
    Model(const std::string &path);
    void draw(GLuint shaderProgram);
    void loadTriangle(GLuint shaderProgram);
    void CoutInfo();

private:
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> textures_loaded;

    void loadModel(const std::string &path);

    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string &typeName);
    Texture loadTexture(const std::string &path, const std::string &type);
};