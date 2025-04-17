/**
  ******************************************************************************
  * @file           : assimp_loader.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-16
  ******************************************************************************
  */

#include "assimp_loader.h"

#include <iostream>

#include "../glframework/object/object.h"
#include "../glframework/object/scene.h"
#include "../glframework/object/group.h"
#include "../glframework/object/mesh.h"
#include "../glframework/tools/tools.h"
#include "../glframework/material/phong_material.h"

std::shared_ptr<Scene> AssimpLoader::load(std::string_view path) {
    Assimp::Importer importer;
    const aiScene *aiscene = importer.ReadFile(path.data(), aiProcess_Triangulate | aiProcess_GenNormals);
    if (aiscene == nullptr || aiscene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || aiscene->mRootNode == nullptr) {
        std::cerr << "Error: Model read failed!" << std::endl;
        return nullptr;
    }
    std::string rootPath{path};
    rootPath = rootPath.substr(0, rootPath.find_last_of("//") + 1);
    std::shared_ptr<Group> group = AssimpLoader::processNode(
            aiscene->mRootNode, aiscene, rootPath);
    auto scene = std::make_shared<Scene>();
    scene->addChild(group);
    scene->setScale(glm::vec3{1.f, 1.f, 1.f});
    return scene;
}

std::shared_ptr<Group> AssimpLoader::processNode(aiNode *ainode, const aiScene *aiscene, std::string_view rootPath) {
    glm::mat4 localMatrix = AssimpLoader::convertToGLMMatrix(ainode->mTransformation);
    glm::vec3 position, angles, scale;
    Tools::decompose(localMatrix, position, angles, scale);
    auto group = std::make_shared<Group>(position, angles.x, angles.y, angles.z, scale);
    for (int i = 0; i < ainode->mNumMeshes; ++i) {
        int meshIndex = ainode->mMeshes[i];
        aiMesh *aimesh = aiscene->mMeshes[meshIndex];
        std::shared_ptr<Mesh> mesh = AssimpLoader::processMesh(aimesh, aiscene, rootPath);
        group->addChild(mesh);
    }
    for (int i = 0; i < ainode->mNumChildren; ++i) {
        std::shared_ptr<Group> childGroup = AssimpLoader::processNode(ainode->mChildren[i], aiscene, rootPath);
        group->addChild(childGroup);
    }
    return group;
}

std::shared_ptr<Mesh> AssimpLoader::processMesh(aiMesh *aimesh, const aiScene *aiscene, std::string_view rootPath) {
    std::vector<float>
            positions(aimesh->mNumVertices * 3),
            normals(aimesh->mNumVertices * 3),
            uvs(aimesh->mNumVertices * 2);
    std::vector<unsigned int> indices;
    // 处理position normals uvs
    for (int i = 0; i < aimesh->mNumVertices; ++i) {
        const aiVector3D &aiVertex = aimesh->mVertices[i];
        const aiVector3D &aiNormal = aimesh->mNormals[i];
        positions[i * 3 + 0] = aiVertex.x;
        positions[i * 3 + 1] = aiVertex.y;
        positions[i * 3 + 2] = aiVertex.z;
        normals[i * 3 + 0] = aiNormal.x;
        normals[i * 3 + 1] = aiNormal.y;
        normals[i * 3 + 2] = aiNormal.z;
        // 索引为0的uv一般为贴图uv
        const aiVector3D *aiUV = aimesh->mTextureCoords[0];
        if (aiUV != nullptr) {
            uvs[i * 2 + 0] = aiUV[i].x;
            uvs[i * 2 + 1] = aiUV[i].y;
        } else { // 默认uv
            uvs[i * 2 + 0] = 0.f;
            uvs[i * 2 + 1] = 0.f;
        }
    }
    // 处理indices
    for (int i = 0; i < aimesh->mNumFaces; ++i) {
        const aiFace &aiface = aimesh->mFaces[i];
        for (int j = 0; j < aiface.mNumIndices; ++j) {
            indices.push_back(aiface.mIndices[j]);
        }
    }
    // 处理texture
    std::shared_ptr<Texture> diffuseTexture{};
    std::shared_ptr<Texture> specularTexture{};
    if (aimesh->mMaterialIndex >= 0) {
        diffuseTexture = AssimpLoader::processTexture(
                aiscene->mMaterials[aimesh->mMaterialIndex],
                aiTextureType_DIFFUSE, aiscene, rootPath, 0);
        specularTexture = AssimpLoader::processTexture(
                aiscene->mMaterials[aimesh->mMaterialIndex],
                aiTextureType_SPECULAR, aiscene, rootPath, 1);
    } else { // 没有material 默认texture
        diffuseTexture = Texture::createTexture("./asserts/textures/default.jpg", 0);
    }
    return std::make_shared<Mesh>(
            std::make_shared<Geometry>(positions, normals, uvs, indices),
            std::make_shared<PhongMaterial>(
                    diffuseTexture,
                    (specularTexture == nullptr) ? Texture::createTexture("./asserts/white.jpg", 1) : specularTexture,
                    0.5)
    );
}

std::shared_ptr<Texture> AssimpLoader::processTexture(
        const aiMaterial *aimaterial,
        const aiTextureType &type,
        const aiScene *scene,
        std::string_view rootPath,
        GLuint unit) {
    aiString aipath{};
    aimaterial->Get(AI_MATKEY_TEXTURE(type, 0), aipath);
    if (aipath.length == 0) {
        return nullptr;
    }
    std::shared_ptr<Texture> result;
    const aiTexture *aitexture = scene->GetEmbeddedTexture(aipath.C_Str());
    // 判断是否为内嵌图片
    if (aitexture == nullptr) { // 图片在硬盘上
        result = Texture::createTexture(std::string{rootPath} + aipath.C_Str(), unit);
    } else { // 内嵌图片
        unsigned char *data = reinterpret_cast<unsigned char *>(aitexture->pcData);
        result = Texture::createTexture(aipath.C_Str(), aitexture->mWidth, aitexture->mHeight, data, unit);
    }
    return result;
}

glm::mat4 AssimpLoader::convertToGLMMatrix(const aiMatrix4x4 &mat4) {
    return glm::mat4{
            mat4.a1, mat4.b1, mat4.c1, mat4.d1,
            mat4.a2, mat4.b2, mat4.c2, mat4.d2,
            mat4.a3, mat4.b3, mat4.c3, mat4.d3,
            mat4.a4, mat4.b4, mat4.c4, mat4.d4
    };
}
