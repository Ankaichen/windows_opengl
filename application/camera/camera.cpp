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

#include "../../glframework/shader.h"

Camera::Camera(const glm::vec3 &position, const glm::vec3 &upVec, const glm::vec3 &rightVec)
        : mPosition{position}, mUpVec{upVec}, mRightVec{rightVec} {}

Camera::~Camera() noexcept = default;

void Camera::addUniformToShader(Shader &shader) const {
    shader.setMatrix4x4("viewMatrix", this->getViewMatrix());
    shader.setMatrix4x4("projectionMatrix", this->getProjectionMatrix());
    shader.setVector3f("cameraPosition", this->getPosition());
}
