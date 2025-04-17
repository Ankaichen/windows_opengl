/**
  ******************************************************************************
  * @file           : scene.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-16
  ******************************************************************************
  */

#ifndef OPENGL_SCENE_H
#define OPENGL_SCENE_H

#include "object.h"

class Scene : public Object {
public:
    Scene() = default;

    Scene(const glm::vec3 &position, float angleX, float angleY, float angleZ, const glm::vec3 &scale);

    ~Scene() = default;
};


#endif //OPENGL_SCENE_H
