/**
  ******************************************************************************
  * @file           : scene.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-16
  ******************************************************************************
  */

#include "scene.h"


Scene::Scene(const glm::vec3 &position, float angleX, float angleY, float angleZ, const glm::vec3 &scale)
        : Object(position, angleX, angleY, angleZ, scale) {
}
