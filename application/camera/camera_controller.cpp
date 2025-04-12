/**
  ******************************************************************************
  * @file           : camera_controller.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-4-10
  ******************************************************************************
  */

#include "camera_controller.h"

#include "camera.h"

CameraController::CameraController(const std::shared_ptr<Camera> &camera, float sensitivity, float scaleSpeed)
        : mCamera{camera}, mSensitivity{sensitivity}, mScaleSpeed{scaleSpeed} {
}

CameraController::CameraController(std::shared_ptr<Camera> &&camera, float sensitivity, float scaleSpeed)
        : mCamera{std::move(camera)}, mSensitivity{sensitivity}, mScaleSpeed{scaleSpeed} {
}

CameraController::~CameraController() noexcept = default;

void CameraController::onMouse(int button, int action, double xpos, double ypos) const {
    bool pressed = (action == GLFW_PRESS);
    if (pressed) {
        this->mCurrentX = static_cast<float>(xpos);
        this->mCurrentY = static_cast<float>(ypos);
    }
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            this->mLeftMouseDown = pressed;
            break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            this->mMiddleMouseDown = pressed;
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            this->mRightMouseDown = pressed;
            break;
        default:
            break;
    }
}

void CameraController::onKey(int key, int action, int mods) const {
    if (action == GLFW_REPEAT) return; // 过滤repeat
    bool pressed = (action == GLFW_PRESS);
    this->mKeyMap[key] = pressed;
}
