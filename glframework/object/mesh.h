/**
  ******************************************************************************
  * @file           : mesh.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-12
  ******************************************************************************
  */

#ifndef OPENGL_MESH_H
#define OPENGL_MESH_H

#include <memory>

#include "object.h"
#include "../material/material.h"
#include "../geometry.h"
#include "../interface/shader_uniformer.h"

class Mesh : public Object {
public:
    Mesh() = default;

    Mesh(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material);

    Mesh(const glm::vec3 &position, float angleX, float angleY, float angleZ, const glm::vec3 &scale,
         std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material);

    ~Mesh() noexcept override;

    inline void setGeometry(std::shared_ptr<Geometry> geometry) { this->mGeometry = std::move(geometry); }

    [[nodiscard]] inline std::shared_ptr<Geometry> getGeometry() const { return this->mGeometry; }

    inline void setMaterial(std::shared_ptr<Material> material) { this->mMaterial = std::move(material); }

    [[nodiscard]] inline std::shared_ptr<Material> getMaterial() const { return this->mMaterial; }

    void addUniformToShader(const std::shared_ptr<Shader> &shader) const override;

    const RenderData getRenderData() const override;

private:
    std::shared_ptr<Geometry> mGeometry{nullptr};
    std::shared_ptr<Material> mMaterial{nullptr};
};


#endif //OPENGL_MESH_H
