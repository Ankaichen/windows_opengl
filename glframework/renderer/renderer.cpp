/**
  ******************************************************************************
  * @file           : renderer.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-12
  ******************************************************************************
  */

#include "renderer.h"

#include "../object/object.h"
#include "../object/mesh.h"
#include "../../application/camera/camera.h"
#include "../light/directional_light.h"
#include "../light/ambient_light.h"
#include "../shader.h"
#include "../material/material.h"

Renderer::~Renderer() noexcept = default;

void Renderer::addShader(MaterialType materialType,
                         std::string_view vertexPath, std::string_view fragmentPath) {
    this->mShaders.insert(
            std::make_pair(materialType, std::make_shared<Shader>(vertexPath, fragmentPath))
    );
}

void Renderer::render(const std::vector<std::shared_ptr<Mesh>> &meshes, const std::shared_ptr<Camera> &camera,
                      const std::vector<std::shared_ptr<Light>> &lights) const {
    // 设置当前帧的OpenGL状态机参数
    GL_CALL(glEnable(GL_DEPTH_TEST));
    GL_CALL(glDepthFunc(GL_LESS));
    GL_CALL(glClearDepth(1.f));
    // 清理画布
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    // 绘制mesh
    for (const auto &mesh: meshes) {
        if (mesh == nullptr) {
            continue;
        }
        const auto &geometry = mesh->getGeometry();
        const auto &material = mesh->getMaterial();
        // 根据material获取shader
        auto iter = this->mShaders.find(material->getMaterialType());
        if (iter == this->mShaders.cend()) {
            continue;
        }
        auto &shader = iter->second;
        shader->begin();
        material->bind();
        // 设置shader的uniform
        shader << mesh << camera;
        for (const auto &light: lights) {
            shader << light;
        }
        // 绑定VAO
        glBindVertexArray(geometry->getVao());
        // 绘制
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(geometry->getIndicesCount()), GL_UNSIGNED_INT,
                       reinterpret_cast<void *>(0));
        shader->end();
        glBindVertexArray(0);
    }
}

void Renderer::renderObject(std::shared_ptr<Object> object, const std::shared_ptr<Camera> &camera,
                            const std::vector<std::shared_ptr<Light>> &lights) const {
    if (object == nullptr) {
        return;
    }
    const auto &geometry = mesh->getGeometry();
    const auto &material = mesh->getMaterial();
    // 根据material获取shader
    auto iter = this->mShaders.find(material->getMaterialType());
    if (iter == this->mShaders.cend()) {
        return;
    }
    auto &shader = iter->second;
    shader->begin();
    material->bind();
    // 设置shader的uniform
    shader << mesh << camera;
    for (const auto &light: lights) {
        shader << light;
    }
    // 绑定VAO
    glBindVertexArray(geometry->getVao());
    // 绘制
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(geometry->getIndicesCount()), GL_UNSIGNED_INT,
                   reinterpret_cast<void *>(0));
    shader->end();
    glBindVertexArray(0);
}
