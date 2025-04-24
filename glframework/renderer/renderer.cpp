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

void Renderer::render(const std::vector<std::shared_ptr<Object>> &objects, const std::shared_ptr<Camera> &camera,
                      const std::vector<std::shared_ptr<Light>> &lights) const {
    // 设置当前帧的OpenGL状态机参数
    GL_CALL(glEnable(GL_DEPTH_TEST));
    GL_CALL(glDepthFunc(GL_LESS));
    GL_CALL(glDepthMask(GL_TRUE));
    GL_CALL(glClearDepth(1.f));
    glDisable(GL_POLYGON_OFFSET_LINE);
    glDisable(GL_POLYGON_OFFSET_FILL);
    // 清理画布
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    // 绘制mesh
    for (const std::shared_ptr<const Object> &object: objects) {
        if (object == nullptr) {
            continue;
        }
        object->visitObjects([this, &camera, &lights](std::shared_ptr<const Object> child) -> void {
            RenderData renderData = child->getRenderData();
            if (!renderData.enable) {
                return;
            }
            auto iter = this->mShaders.find(renderData.materialType);
            if (iter == this->mShaders.end()) {
                return;
            }
            auto &shader = iter->second;
            shader->begin();
            shader << child << camera;
            for (const auto &light: lights) {
                shader << light;
            }
            // 绑定VAO
            glBindVertexArray(renderData.vao);
            // 绘制
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(renderData.indicesCount), GL_UNSIGNED_INT,
                           reinterpret_cast<void *>(0));
            shader->end();
            glBindVertexArray(0);
        });
    }
}
