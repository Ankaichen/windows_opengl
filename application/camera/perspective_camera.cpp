/**
  ******************************************************************************
  * @file           : perspective_camera.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-4-9
  ******************************************************************************
  */

#include "perspective_camera.h"

PerspectiveCamera::PerspectiveCamera(float fovy, float aspect, float near, float far)
        : Camera(), mFovy{fovy}, mAspect{aspect}, mNear{near}, mFar{far} {
}

PerspectiveCamera::PerspectiveCamera(const glm::vec3 &position, const glm::vec3 &up_vec, const glm::vec3 &right_vec,
                                     float fovy, float aspect, float near, float far)
        : Camera{position, up_vec, right_vec}, mFovy{fovy}, mAspect{aspect}, mNear{near}, mFar{far} {
}

void PerspectiveCamera::scale(float delta_scale) {
    glm::vec3 front = glm::cross(this->mRightVec, this->mUpVec);
    this->mPosition += (front * delta_scale);
}
