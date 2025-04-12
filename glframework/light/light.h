/**
  ******************************************************************************
  * @file           : light.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-12
  ******************************************************************************
  */

#ifndef OPENGL_LIGHT_H
#define OPENGL_LIGHT_H


#include "../core.h"

class Light {
public:
    Light() = default;

    Light(const glm::vec3 &color, float specularIntensity);

    virtual ~Light() noexcept = 0;

    inline void setColor(const glm::vec3 &color) { this->mColor = color; }

    [[nodiscard]] inline glm::vec3 getColor() const { return this->mColor; }

    inline void setSpecularIntensity(float specularIntensity) { this->mSpecularIntensity = specularIntensity; }

    [[nodiscard]] inline float getSpecularIntensity() const { return this->mSpecularIntensity; }

private:
    glm::vec3 mColor{1.f};
    float mSpecularIntensity{1.f};
};


#endif //OPENGL_LIGHT_H
