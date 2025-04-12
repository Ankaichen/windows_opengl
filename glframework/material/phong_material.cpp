/**
  ******************************************************************************
  * @file           : phong_material.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-12
  ******************************************************************************
  */

#include "phong_material.h"

#include "../shader.h"

PhongMaterial::PhongMaterial() : Material(MaterialType::PHONG_MATERIAL) {
}

PhongMaterial::PhongMaterial(std::shared_ptr<Texture> diffuse, float shiness)
        : Material(MaterialType::PHONG_MATERIAL), mDiffuse{std::move(diffuse)}, mShiness{shiness} {
}

PhongMaterial::~PhongMaterial() noexcept = default;

void PhongMaterial::addUniformToShader(Shader &shader) const {
    this->mDiffuse->bind();
    shader.setInt("sampler", this->mDiffuse->getUnit());
    shader.setFloat("shiness", this->mShiness);
}