/**
  ******************************************************************************
  * @file           : material.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-12
  ******************************************************************************
  */

#ifndef OPENGL_MATERIAL_H
#define OPENGL_MATERIAL_H

#include "../shader_uniformer.h"

enum class MaterialType {
    PHONG_MATERIAL, WHITE_MATERIAL
};

class Material : public ShaderUniformer {
public:
public:
    explicit Material(MaterialType materialType);

    ~Material() noexcept override = 0;

    virtual void bind() const = 0;

    [[nodiscard]] inline MaterialType getMaterialType() const { return this->mMaterialType; }

protected:
    const MaterialType mMaterialType{};
};


#endif //OPENGL_MATERIAL_H
