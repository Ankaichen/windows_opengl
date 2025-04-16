/**
  ******************************************************************************
  * @file           : spot_light.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-14
  ******************************************************************************
  */

#ifndef OPENGL_SPOT_LIGHT_H
#define OPENGL_SPOT_LIGHT_H

#include "light.h"
#include "../object.h"
#include "../../utils/auto_id.h"

class SpotLight : public Light, public Object, public AutoId<SpotLight> {
public:
    SpotLight() = default;

    SpotLight(const glm::vec3 &color, float specularIntensity, const glm::vec3 &position,
              const glm::vec3 &targetDirection, float innerAngle, float outerAngle);

    ~SpotLight() noexcept override;

    void addUniformToShader(const std::shared_ptr<Shader> &shader) const override;

private:
    glm::vec3 mTargetDirection{-1.f};
    float mInnerAngle{0.f};
    float mOuterAngle{0.f};
};


#endif //OPENGL_SPOT_LIGHT_H
