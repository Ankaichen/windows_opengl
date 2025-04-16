/**
  ******************************************************************************
  * @file           : mesh.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-12
  ******************************************************************************
  */

#include "mesh.h"
#include "shader.h"

Mesh::Mesh(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material)
        : Object(), mGeometry(std::move(geometry)), mMaterial(std::move(material)) {
}

Mesh::Mesh(const glm::vec3 &position, float angleX, float angleY, float angleZ, const glm::vec3 &scale,
           std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material)
        : Object(position, angleX, angleY, angleZ, scale), mGeometry(std::move(geometry)),
          mMaterial(std::move(material)) {
}

Mesh::~Mesh() noexcept {

}

void Mesh::addUniformToShader(const std::shared_ptr<Shader> &shader) const {
    Object::addUniformToShader(shader);
    shader << this->mMaterial;
}
