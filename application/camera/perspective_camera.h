/**
  ******************************************************************************
  * @file           : perspective_camera.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-4-9
  ******************************************************************************
  */

#ifndef OPENGL_PERSPECTIVE_CAMERA_H
#define OPENGL_PERSPECTIVE_CAMERA_H

#include "camera.h"

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera() = default;

    PerspectiveCamera(float fovy, float aspect, float near, float far);

    PerspectiveCamera(const glm::vec3 &position, const glm::vec3 &upVec, const glm::vec3 &rightVec, float fovy,
                      float aspect, float near, float far);

    ~PerspectiveCamera() noexcept override = default;

    [[nodiscard]] inline glm::mat4 getProjectionMatrix() const override {
        return glm::perspective(glm::radians(this->mFovy), this->mAspect, this->mNear, this->mFar);
    }

    void scale(float deltaScale) override;

private:
    float mFovy{0.f};
    float mAspect{0.f};
};


#endif //OPENGL_PERSPECTIVE_CAMERA_H
