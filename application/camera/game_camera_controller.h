/**
  ******************************************************************************
  * @file           : game_camera_controller.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-4-10
  ******************************************************************************
  */

#ifndef OPENGL_GAME_CAMERA_CONTROLLER_H
#define OPENGL_GAME_CAMERA_CONTROLLER_H

#include "camera_controller.h"

class GameCameraController : public CameraController {
public:
    GameCameraController() = default;

    GameCameraController(const std::shared_ptr<Camera> &camera, float sensitivity, float scale, float speed);

    GameCameraController(std::shared_ptr<Camera> &&camera, float sensitivity, float scale, float speed);

    ~GameCameraController() noexcept override = default;

    void onCurse(double xpos, double ypos) const override;

    void update() const override;

    void onScroll(float offset) const override;

private:
    void pitch(float angle) const;

    void yaw(float angle) const;

private:
    float mSpeed{0.1f};
    mutable float mPitch{0.f};
};


#endif //OPENGL_GAME_CAMERA_CONTROLLER_H
