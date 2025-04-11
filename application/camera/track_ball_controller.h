/**
  ******************************************************************************
  * @file           : track_ball_controller.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-4-10
  ******************************************************************************
  */

#ifndef OPENGL_TRACK_BALL_CONTROLLER_H
#define OPENGL_TRACK_BALL_CONTROLLER_H

#include "camera_controller.h"

class TrackBallController : public CameraController {
public:
    TrackBallController() = default;
    TrackBallController(const std::shared_ptr<Camera> &camera, float sensitivity, float scale, float move_speed);
    TrackBallController(std::shared_ptr<Camera> &&camera, float sensitivity, float scale, float move_speed);

    void onCurse(double xpos, double ypos) const override;
    void onScroll(float offset) const override;
    void update() const override {}

private:
    void pitch(float angle) const;
    void yaw(float angle) const;

private:
    float mMoveSpeed{ 0.005f };
};


#endif //OPENGL_TRACK_BALL_CONTROLLER_H
