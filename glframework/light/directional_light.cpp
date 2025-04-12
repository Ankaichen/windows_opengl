/**
  ******************************************************************************
  * @file           : directional_light.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-12
  ******************************************************************************
  */

#include "directional_light.h"

DirectionalLight::DirectionalLight(const glm::vec3 &color, float specularIntensity, const glm::vec3 &direction)
        : Light(color, specularIntensity), mDirection{direction} {
}

DirectionalLight::~DirectionalLight() noexcept {
}
