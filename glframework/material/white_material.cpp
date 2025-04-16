/**
  ******************************************************************************
  * @file           : white_material.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-13
  ******************************************************************************
  */

#include "white_material.h"

WhiteMaterial::WhiteMaterial()
        : Material(MaterialType::WHITE_MATERIAL) {
}

WhiteMaterial::~WhiteMaterial() noexcept {
}

void WhiteMaterial::addUniformToShader(const std::shared_ptr<Shader> &shader) const {
}
