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

#include <string>
#include <sstream>

#include "../shader.h"

DirectionalLight::DirectionalLight(const glm::vec3 &color, float specularIntensity, const glm::vec3 &direction)
        : Light(color, specularIntensity), mDirection{direction} {
}

DirectionalLight::~DirectionalLight() noexcept {
}

void DirectionalLight::addUniformToShader(const std::shared_ptr<Shader> &shader) const {
    std::stringstream ss;
    ss << "directionalLights[" << this->getId() << "]";
    std::string uniformName{ss.str()};
    shader->setVector3f(uniformName + ".direction", this->getDirection());
    shader->setVector3f(uniformName + ".color", this->getColor());
    shader->setFloat(uniformName + ".specularIntensity", this->getSpecularIntensity());
}