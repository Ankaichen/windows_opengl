/**
  ******************************************************************************
  * @file           : group.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-4-17
  ******************************************************************************
  */

#ifndef OPENGL_GROUP_H
#define OPENGL_GROUP_H

#include "object.h"

class Group : public Object {
public:
    Group() = default;

    Group(const glm::vec3 &position, float angleX, float angleY, float angleZ, const glm::vec3 &scale);

    ~Group() = default;
};


#endif //OPENGL_GROUP_H
