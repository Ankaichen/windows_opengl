/**
  ******************************************************************************
  * @file           : depth_material.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-4-24
  ******************************************************************************
  */

#include "depth_material.h"

DepthMaterial::DepthMaterial() : Material(MaterialType::DEPTH_MATERIAL) {}

void DepthMaterial::addUniformToShader(const std::shared_ptr<Shader> &shader) const {
}
