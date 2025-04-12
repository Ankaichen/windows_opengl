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

#include "../shader.h"

DirectionalLight::DirectionalLight(const glm::vec3 &color, float specularIntensity, const glm::vec3 &direction)
        : Light(color, specularIntensity), mDirection{direction} {
}

DirectionalLight::~DirectionalLight() noexcept {
}

void DirectionalLight::addUniformToShader(Shader &shader) const {
    shader.setVector3f("lightDirection", this->getDirection());
    shader.setVector3f("lightColor", this->getColor());
    shader.setFloat("specularIntensity", this->getSpecularIntensity());
}
