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

PerspectiveCamera::PerspectiveCamera(const glm::vec3 &position, const glm::vec3 &upVec, const glm::vec3 &rightVec,
                                     float fovy, float aspect, float near, float far)
        : Camera{position, upVec, rightVec}, mFovy{fovy}, mAspect{aspect}, mNear{near}, mFar{far} {
}

void PerspectiveCamera::scale(float deltaScale) {
    glm::vec3 front = glm::cross(this->mRightVec, this->mUpVec);
    this->mPosition += (front * deltaScale);
}
