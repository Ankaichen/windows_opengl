/**
  ******************************************************************************
  * @file           : depth_material.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-4-24
  ******************************************************************************
  */

#ifndef OPENGL_DEPTH_MATERIAL_H
#define OPENGL_DEPTH_MATERIAL_H

#include "material.h"

class DepthMaterial : public Material {
public:
    DepthMaterial();

    ~DepthMaterial() noexcept override = default;

    void addUniformToShader(const std::shared_ptr<Shader> &shader) const override;
};


#endif //OPENGL_DEPTH_MATERIAL_H
