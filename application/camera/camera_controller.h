/**
  ******************************************************************************
  * @file           : camera_controller.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-4-10
  ******************************************************************************
  */

#ifndef OPENGL_CAMERA_CONTROLLER_H
#define OPENGL_CAMERA_CONTROLLER_H

#include <map>
#include <memory>

#include "../../glframework/core.h"

class Camera;

class CameraController {
public:
    CameraController() = default;

    CameraController(const std::shared_ptr<Camera> &camera, float sensitivity, float scale_speed);
    CameraController(std::shared_ptr<Camera> &&camera, float sensitivity, float scale_speed);

    virtual ~CameraController() = 0;

    virtual void onMouse(int button, int action, double xpos, double ypos) const;

    virtual void onCurse(double xpos, double ypos) const = 0;

    virtual void onKey(int key, int action, int mods) const;

    virtual void onScroll(float offset) const = 0;

    virtual void update() const = 0;

    inline void setCamera(const std::shared_ptr<Camera> &camera) { this->mCamera = camera; }
    inline void setCamera(std::shared_ptr<Camera> &&camera) { this->mCamera = std::move(camera); }

    inline void setSensitivity(float sensitivity) { this->mSensitivity = sensitivity; }

    inline void setScale(float scale_speed) { this->mScaleSpeed = scale_speed; }

protected:
    std::shared_ptr<Camera> mCamera{nullptr};
    // 鼠标移动敏感度
    float mSensitivity{0.2f};
    // 相机缩放的速度
    float mScaleSpeed{0.2f};

    // 鼠标按键状态
    mutable bool mLeftMouseDown{false};
    mutable bool mMiddleMouseDown{false};
    mutable bool mRightMouseDown{false};
    // 当前鼠标位置
    mutable float mCurrentX{0.f}, mCurrentY{0.f};
    // 记录键盘相关按键的状态
    mutable std::map<int, bool> mKeyMap;
};


#endif //OPENGL_CAMERA_CONTROLLER_H
