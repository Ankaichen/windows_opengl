/**
  ******************************************************************************
  * @file           : camera.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-4-9
  ******************************************************************************
  */

#include "camera.h"

Camera::Camera(const glm::vec3 &position, const glm::vec3 &up_vec, const glm::vec3 &right_vec)
        : mPosition{position}, mUpVec{up_vec}, mRightVec{right_vec} {}

Camera::~Camera() {}
