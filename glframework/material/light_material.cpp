/**
  ******************************************************************************
  * @file           : white_material.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-13
  ******************************************************************************
  */

#include "light_material.h"

#include "../shader.h"

LightMaterial::LightMaterial(const glm::vec3 &color)
        : Material(MaterialType::LIGHT_MATERIAL), mColor(color) {
}

LightMaterial::~LightMaterial() noexcept {
}

void LightMaterial::addUniformToShader(const std::shared_ptr<Shader> &shader) const {
    shader->setVector3f("lightColor", this->mColor);
    this->bind();
}
