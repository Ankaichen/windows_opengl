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
        : Camera{}, mLeft{left}, mRight{right}, mBottom{bottom}, mTop{top}, mNear{near}, mFar{far} {
}


OrthographicCamera::OrthographicCamera(const glm::vec3 &position, const glm::vec3 &up_vec, const glm::vec3 &right_vec,
                                       float left, float right, float bottom, float top, float near, float far)
        : Camera{position, up_vec, right_vec}, mLeft{left}, mRight{right}, mBottom{bottom}, mTop{top},
          mNear{near}, mFar{far} {
}

void OrthographicCamera::scale(float delta_scale) {
    this->mScale += delta_scale;
}
