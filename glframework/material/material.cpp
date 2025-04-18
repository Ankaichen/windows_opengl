/**
  ******************************************************************************
  * @file           : material.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-12
  ******************************************************************************
  */

#include "material.h"

Material::Material(MaterialType materialType) : mMaterialType(materialType) {
}

Material::~Material() noexcept = default;
