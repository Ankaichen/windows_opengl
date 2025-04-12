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
#include "material/material.h"
#include "geometry.h"

class Mesh : public Object {
public:
    Mesh() = default;

    Mesh(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material);

    ~Mesh() noexcept;

    inline void setGeometry(std::shared_ptr<Geometry> geometry) { this->mGeometry = std::move(geometry); }

    [[nodiscard]] inline std::shared_ptr<Geometry> getGeometry() const { return this->mGeometry; }

    inline void setMaterial(std::shared_ptr<Material> material) { this->mMaterial = std::move(material); }

    [[nodiscard]] inline std::shared_ptr<Material> getMaterial() const { return this->mMaterial; }

private:
    std::shared_ptr<Geometry> mGeometry{nullptr};
    std::shared_ptr<Material> mMaterial{nullptr};
};


#endif //OPENGL_MESH_H
