/**
  ******************************************************************************
  * @file           : spot_light.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-14
  ******************************************************************************
  */

#include "spot_light.h"

#include <string>
#include <sstream>

#include "../shader.h"

SpotLight::SpotLight(const glm::vec3 &color, float specularIntensity, const glm::vec3 &position,
                     const glm::vec3 &targetDirection, float innerAngle, float outerAngle)
        : Light(color, specularIntensity), Object(position, 0.f, 0.f, 0.f, glm::vec3{1.f, 1.f, 1.f}),
          mTargetDirection{targetDirection}, mInnerAngle{innerAngle}, mOuterAngle{outerAngle} {
}

SpotLight::~SpotLight() noexcept {
}

void SpotLight::addUniformToShader(Shader &shader) const {
    std::stringstream ss;
    ss << "spotLights[" << this->getId() << "]";
    std::string uniformName{ss.str()};
    shader.setVector3f(uniformName + ".position", this->getPosition());
    shader.setVector3f(uniformName + ".targetDirection", this->mTargetDirection);
    shader.setVector3f(uniformName + ".color", this->getColor());
    shader.setFloat(uniformName + ".innerLine", glm::cos(glm::radians(this->mInnerAngle)));
    shader.setFloat(uniformName + ".outerLine", glm::cos(glm::radians(this->mOuterAngle)));
    shader.setFloat(uniformName + ".specularIntensity", this->getSpecularIntensity());
}
