/**
  ******************************************************************************
  * @file           : point_light.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-13
  ******************************************************************************
  */

#include "point_light.h"
#include "../shader.h"

PointLight::PointLight(const glm::vec3 &color, float specularIntensity, const glm::vec3 &position,
                       float k2, float k1, float kc)
        : Light(color, specularIntensity), Object(position, 0.f, 0.f, 0.f, glm::vec3{1.f, 1.f, 1.f}), mK2{k2}, mK1{k1},
          mKc{kc} {
}


PointLight::~PointLight() noexcept {
}

void PointLight::addUniformToShader(Shader &shader) const {
    shader.setVector3f("lightPosition", this->getPosition());
    shader.setVector3f("lightColor", this->getColor());
    shader.setFloat("specularIntensity", this->getSpecularIntensity());
    shader.setFloat("k2", this->mK2);
    shader.setFloat("k1", this->mK1);
    shader.setFloat("kc", this->mKc);
}