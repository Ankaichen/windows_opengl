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


class Material {
public:
    Material() = default;

    virtual ~Material() noexcept = 0;
};


#endif //OPENGL_MATERIAL_H
