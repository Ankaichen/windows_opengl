/**
  ******************************************************************************
  * @file           : light.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-12
  ******************************************************************************
  */

#include "light.h"

Light::Light(const glm::vec3 &color, float specularIntensity)
        : mColor{color}, mSpecularIntensity{specularIntensity} {
}

Light::~Light() noexcept {
}
