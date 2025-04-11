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

CameraController::CameraController(const std::shared_ptr<Camera> &camera, float sensitivity, float scale_speed)
        : mCamera{camera}, mSensitivity{sensitivity}, mScaleSpeed{scale_speed} {
}

CameraController::CameraController(std::shared_ptr<Camera> &&camera, float sensitivity, float scale_speed)
        : mCamera{std::move(camera)}, mSensitivity{sensitivity}, mScaleSpeed{scale_speed} {
}

CameraController::~CameraController() {}

void CameraController::onMouse(int button, int action, double xpos, double ypos) const {
    bool pressed = (action == GLFW_PRESS);
    if (pressed) {
        this->mCurrentX = xpos;
        this->mCurrentY = ypos;
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
    }
}

void CameraController::onKey(int key, int action, int mods) const {
    if (action == GLFW_REPEAT) return; // 过滤repeat
    bool pressed = (action == GLFW_PRESS);
    this->mKeyMap[key] = pressed;
}
