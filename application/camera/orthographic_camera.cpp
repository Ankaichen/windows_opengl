/**
  ******************************************************************************
  * @file           : orthographic_camera.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-4-9
  ******************************************************************************
  */

#include "orthographic_camera.h"

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far)
        : Camera{near, far}, mLeft{left}, mRight{right}, mBottom{bottom}, mTop{top} {
}

OrthographicCamera::OrthographicCamera(const glm::vec3 &position, const glm::vec3 &upVec, const glm::vec3 &rightVec,
                                       float left, float right, float bottom, float top, float near, float far)
        : Camera{position, upVec, rightVec, near, far}, mLeft{left}, mRight{right}, mBottom{bottom}, mTop{top} {
}

void OrthographicCamera::scale(float deltaScale) {
    this->mScale += deltaScale;
}
