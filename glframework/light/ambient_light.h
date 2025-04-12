/**
  ******************************************************************************
  * @file           : ambient_light.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-12
  ******************************************************************************
  */

#ifndef OPENGL_AMBIENT_LIGHT_H
#define OPENGL_AMBIENT_LIGHT_H

#include "light.h"

class AmbientLight : public Light {
public:
    AmbientLight() = default;

    AmbientLight(const glm::vec3 &color, float specularIntensity);

    ~AmbientLight() noexcept override;
};


#endif //OPENGL_AMBIENT_LIGHT_H
