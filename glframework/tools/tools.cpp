/**
  ******************************************************************************
  * @file           : tools.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-16
  ******************************************************************************
  */

#include "tools.h"

void Tools::decompose(const glm::mat4 &matrix, glm::vec3 &position, glm::vec3 &angles, glm::vec3 scale) {
    // 四元数
    glm::quat quaternion;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(matrix, scale, quaternion, position, skew, perspective);
    // 四元数转欧拉角
    glm::mat4 rotation = glm::toMat4(quaternion);
    glm::extractEulerAngleXYZ(rotation, angles.x, angles.y, angles.z);
    // 弧度转角度
    angles.x = glm::degrees(angles.x);
    angles.y = glm::degrees(angles.y);
    angles.z = glm::degrees(angles.z);
}
