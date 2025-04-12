/**
  ******************************************************************************
  * @file           : ambient_light.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-12
  ******************************************************************************
  */

#include "ambient_light.h"

AmbientLight::AmbientLight(const glm::vec3 &color, float specularIntensity)
        : Light{color, specularIntensity} {
}

AmbientLight::~AmbientLight() noexcept {
}
