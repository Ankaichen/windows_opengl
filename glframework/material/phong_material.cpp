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

PhongMaterial::PhongMaterial(std::shared_ptr<Texture> diffuse, std::shared_ptr<Texture> specularMask, float shiness)
        : Material(MaterialType::PHONG_MATERIAL), mDiffuse{std::move(diffuse)}, mSpecularMask{std::move(specularMask)},
          mShiness{shiness} {
}

PhongMaterial::~PhongMaterial() noexcept = default;

void PhongMaterial::bind() const {
    this->mDiffuse->bind();
    this->mSpecularMask->bind();
}

void PhongMaterial::addUniformToShader(Shader &shader) const {
    shader.setInt("samplerDiffuse", this->mDiffuse->getUnit());
    shader.setInt("samplerSpecularMask", this->mSpecularMask->getUnit());
    shader.setFloat("shiness", this->mShiness);
}