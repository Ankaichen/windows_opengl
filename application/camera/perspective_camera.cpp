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
#include "../../glframework/shader.h"

PerspectiveCamera::PerspectiveCamera(float fovy, float aspect, float near, float far)
        : Camera(near, far), mFovy{fovy}, mAspect{aspect} {
}

PerspectiveCamera::PerspectiveCamera(const glm::vec3 &position, const glm::vec3 &upVec, const glm::vec3 &rightVec,
                                     float fovy, float aspect, float near, float far)
        : Camera{position, upVec, rightVec, near, far}, mFovy{fovy}, mAspect{aspect} {
}

void PerspectiveCamera::scale(float deltaScale) {
    glm::vec3 front = glm::cross(this->mRightVec, this->mUpVec);
    this->mPosition += (front * deltaScale);
}
