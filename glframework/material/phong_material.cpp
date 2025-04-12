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

PhongMaterial::PhongMaterial(std::shared_ptr<Texture> diffuse, float shiness)
        : mDiffuse{std::move(diffuse)}, mShiness{shiness} {
}

PhongMaterial::~PhongMaterial() noexcept {
}
