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

#include "../shader.h"

AmbientLight::AmbientLight(const glm::vec3 &color)
        : Light{color, 0.f} {
}

AmbientLight::~AmbientLight() noexcept {
}

void AmbientLight::addUniformToShader(Shader &shader) const {
    shader.setVector3f("ambientColor", this->getColor());
}
