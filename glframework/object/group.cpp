/**
  ******************************************************************************
  * @file           : group.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-4-17
  ******************************************************************************
  */

#include "group.h"

Group::Group(const glm::vec3 &position, float angleX, float angleY, float angleZ, const glm::vec3 &scale)
        : Object(position, angleX, angleY, angleZ, scale) {
}
