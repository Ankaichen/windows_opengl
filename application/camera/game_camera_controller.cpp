/**
  ******************************************************************************
  * @file           : game_camera_controller.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-4-10
  ******************************************************************************
  */

#include "game_camera_controller.h"

#include "camera.h"

GameCameraController::GameCameraController(const std::shared_ptr<Camera> &camera, float sensitivity, float scale,
                                           float speed)
        : CameraController{camera, sensitivity, scale}, mSpeed{speed} {
}

GameCameraController::GameCameraController(std::shared_ptr<Camera> &&camera, float sensitivity, float scale,
                                           float speed)
        : CameraController{std::move(camera), sensitivity, scale}, mSpeed{speed} {
}

void GameCameraController::onCurse(double xpos, double ypos) const {
    if (this->mLeftMouseDown) {
        double delta_x{xpos - this->mCurrentX}, delta_y{ypos - this->mCurrentY};
        this->pitch(delta_y * this->mSensitivity);
        this->yaw(delta_x * this->mSensitivity);
    }
    this->mCurrentX = xpos;
    this->mCurrentY = ypos;
}

void GameCameraController::update() const {
    glm::vec3 direction{0.f};
    glm::vec3 front = glm::cross(this->mCamera->getUpVec(), this->mCamera->getRightVec());
    if (this->mKeyMap[GLFW_KEY_W]) {
        direction += front;
    }
    if (this->mKeyMap[GLFW_KEY_A]) {
        direction -= this->mCamera->getRightVec();
    }
    if (this->mKeyMap[GLFW_KEY_S]) {
        direction -= front;
    }
    if (this->mKeyMap[GLFW_KEY_D]) {
        direction += this->mCamera->getRightVec();
    }
    if (glm::length(direction) > 0.00001f) {
        this->mCamera->setPosition(this->mCamera->getPosition() + glm::normalize(direction) * this->mSpeed);
    }
}

void GameCameraController::pitch(float angle) const {

    this->mPitch += angle;
    this->mPitch = std::min(std::max(this->mPitch, 89.f), -89.f);

    glm::mat4 mat = glm::rotate(glm::identity<glm::mat4>(), glm::radians(angle), this->mCamera->getRightVec());
    this->mCamera->setUpVec(mat * glm::vec4{this->mCamera->getUpVec(), 0.f});
}

void GameCameraController::yaw(float angle) const {
    glm::mat4 mat = glm::rotate(glm::identity<glm::mat4>(), glm::radians(angle), glm::vec3{0.f, 1.f, 0.f});
    this->mCamera->setRightVec(mat * glm::vec4{this->mCamera->getRightVec(), 0.f});
    this->mCamera->setUpVec(mat * glm::vec4{this->mCamera->getUpVec(), 0.f});
}

void GameCameraController::onScroll(float offset) const {
    this->mCamera->scale(-offset * this->mScaleSpeed);
}
