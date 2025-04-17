/**
  ******************************************************************************
  * @file           : assimp_loader.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-16
  ******************************************************************************
  */

#ifndef OPENGL_ASSIMP_LOADER_H
#define OPENGL_ASSIMP_LOADER_H

#include "../glframework/core.h"

#include <string_view>
#include <memory>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class Object;

class Scene;

class Group;

class Mesh;

class Texture;

class AssimpLoader {
public:
    static std::shared_ptr<Scene> load(std::string_view path);

private:
    static std::shared_ptr<Group> processNode(aiNode *ainode, const aiScene *aiscene, std::string_view rootPath);

    static std::shared_ptr<Mesh> processMesh(aiMesh *aimesh, const aiScene *aiscene, std::string_view rootPath);

    static std::shared_ptr<Texture> processTexture(
            const aiMaterial *aimaterial,
            const aiTextureType &type,
            const aiScene *scene,
            std::string_view rootPath);

    static glm::mat4 convertToGLMMatrix(const aiMatrix4x4 &mat4);
};


#endif //OPENGL_ASSIMP_LOADER_H
