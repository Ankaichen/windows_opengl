/**
  ******************************************************************************
  * @file           : point_light.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-13
  ******************************************************************************
  */

#ifndef OPENGL_POINT_LISGT_H
#define OPENGL_POINT_LISGT_H

#include "light.h"
#include "../object.h"

class PointLight : public Light, public Object {
public:
    PointLight() = default;

    PointLight(const glm::vec3 &color, float specularIntensity, const glm::vec3 &position,
               float k2, float k1, float kc);

    ~PointLight() noexcept;

    void addUniformToShader(Shader &shader) const override;

private:
    float mK2{1.f}, mK1{1.f}, mKc{1.f};
};


#endif //OPENGL_POINT_LISGT_H
