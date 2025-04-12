/**
  ******************************************************************************
  * @file           : phong_material.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-12
  ******************************************************************************
  */

#ifndef OPENGL_PHONG_MATREIAL_H
#define OPENGL_PHONG_MATREIAL_H

#include <memory>

#include "../texture.h"

class PhongMaterial {
public:
    PhongMaterial() = default;

    PhongMaterial(std::shared_ptr<Texture> diffuse, float shiness);

    ~PhongMaterial() noexcept;

    void setDiffuse(std::shared_ptr<Texture> diffuse) { this->mDiffuse = std::move(diffuse); }

    [[nodiscard]] std::shared_ptr<Texture> getDiffuse() const { return this->mDiffuse; }

    void setShiness(float shiness) { this->mShiness = shiness; }

    [[nodiscard]] float getShiness() const { return this->mShiness; }

private:
    std::shared_ptr<Texture> mDiffuse{nullptr};
    float mShiness{1.f};
};


#endif //OPENGL_PHONG_MATREIAL_H
