/**
  ******************************************************************************
  * @file           : white_material.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-13
  ******************************************************************************
  */

#ifndef OPENGL_LIGHT_MATERIAL_H
#define OPENGL_LIGHT_MATERIAL_H

#include "../core.h"
#include "material.h"

class LightMaterial : public Material {
public:
    LightMaterial(const glm::vec3 &color);

    ~LightMaterial() noexcept override;

    void bind() const override {}

    void addUniformToShader(const std::shared_ptr<Shader> &shader) const override;

private:
    glm::vec3 mColor{0.f};
};


#endif //OPENGL_LIGHT_MATERIAL_H
