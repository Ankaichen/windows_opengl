/**
  ******************************************************************************
  * @file           : white_material.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-13
  ******************************************************************************
  */

#ifndef OPENGL_WHITE_MATERIAL_H
#define OPENGL_WHITE_MATERIAL_H

#include "material.h"

class WhiteMaterial : public Material {
public:
    WhiteMaterial();

    ~WhiteMaterial() noexcept override;

    void bind() const override {}

    void addUniformToShader(Shader &shader) const override;
};


#endif //OPENGL_WHITE_MATERIAL_H
