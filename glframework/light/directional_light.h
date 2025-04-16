/**
  ******************************************************************************
  * @file           : directional_light.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-12
  ******************************************************************************
  */

#ifndef OPENGL_DIRECTIONAL_LIGHT_H
#define OPENGL_DIRECTIONAL_LIGHT_H

#include "../core.h"
#include "light.h"
#include "../../utils/auto_id.h"

class DirectionalLight : public Light, public AutoId<DirectionalLight> {
public:
    DirectionalLight() = default;

    DirectionalLight(const glm::vec3 &color, float specularIntensity, const glm::vec3 &direction);

    ~DirectionalLight() noexcept override;

    inline void setDirection(const glm::vec3 &direction) { this->mDirection = direction; }

    [[nodiscard]] inline glm::vec3 getDirection() const { return this->mDirection; }

    void addUniformToShader(const std::shared_ptr<Shader> &shader) const override;

private:
    glm::vec3 mDirection{-1.f};
};


#endif //OPENGL_DIRECTIONAL_LIGHT_H
