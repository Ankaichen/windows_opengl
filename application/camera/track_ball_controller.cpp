/**
  ******************************************************************************
  * @file           : track_ball_controller.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-4-10
  ******************************************************************************
  */

#include "track_ball_controller.h"

#include "camera.h"

TrackBallController::TrackBallController(const std::shared_ptr<Camera> &camera, float sensitivity, float scale,
                                         float move_speed)
        : CameraController{camera, sensitivity, scale}, mMoveSpeed{move_speed} {
}

TrackBallController::TrackBallController(std::shared_ptr<Camera> &&camera, float sensitivity, float scale,
                                         float move_speed)
        : CameraController{std::move(camera), sensitivity, scale}, mMoveSpeed{move_speed} {
}

void TrackBallController::onCurse(double xpos, double ypos) const {
    if (this->mLeftMouseDown) { // 改变角度
        double delta_x{xpos - this->mCurrentX}, delta_y{ypos - this->mCurrentY};
        this->pitch(-delta_y * this->mSensitivity);
        this->yaw(-delta_x * this->mSensitivity);
    } else if (this->mMiddleMouseDown) { // 改变位置
        float delta_x{static_cast<float>(xpos - this->mCurrentX)}, delta_y{static_cast<float>(ypos - this->mCurrentY)};
        this->mCamera->setPosition(
                this->mCamera->getPosition() + this->mCamera->getUpVec() * delta_y * this->mMoveSpeed);
        this->mCamera->setPosition(
                this->mCamera->getPosition() - this->mCamera->getRightVec() * delta_x * this->mMoveSpeed);
    }
    this->mCurrentX = xpos;
    this->mCurrentY = ypos;
}

void TrackBallController::onScroll(float offset) const {
    this->mCamera->scale(-offset * this->mScaleSpeed);
}

void TrackBallController::pitch(float angle) const {
    // 绕着mRight向量旋转
    glm::mat4 mat = glm::rotate(glm::identity<glm::mat4>(), glm::radians(angle), this->mCamera->getRightVec());
    this->mCamera->setPosition(mat * glm::vec4{this->mCamera->getPosition(), 0.f});
    this->mCamera->setUpVec(mat * glm::vec4{this->mCamera->getUpVec(), 1.f});
}

void TrackBallController::yaw(float angle) const {
    // 绕着世界坐标系的y轴旋转
    glm::mat4 mat = glm::rotate(glm::identity<glm::mat4>(), glm::radians(angle), glm::vec3{0.f, 1.f, 0.f});
    this->mCamera->setPosition(mat * glm::vec4{this->mCamera->getPosition(), 0.f});
    this->mCamera->setUpVec(mat * glm::vec4{this->mCamera->getUpVec(), 1.f});
    this->mCamera->setRightVec(mat * glm::vec4{this->mCamera->getRightVec(), 1.f});
}
