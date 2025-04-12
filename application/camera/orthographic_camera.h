/**
  ******************************************************************************
  * @file           : orthographic_camera.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-4-9
  ******************************************************************************
  */

#ifndef OPENGL_ORTHOGRAPHIC_CAMERA_H
#define OPENGL_ORTHOGRAPHIC_CAMERA_H

#include "camera.h"

class OrthographicCamera : public Camera {
public:
    OrthographicCamera() = default;

    OrthographicCamera(float left, float right, float bottom, float top, float near, float far);

    OrthographicCamera(const glm::vec3 &position, const glm::vec3 &upVec, const glm::vec3 &rightVec, float left,
                       float right, float bottom, float top, float near, float far);

    ~OrthographicCamera() noexcept override = default;

    [[nodiscard]] inline glm::mat4 getProjectionMatrix() const override {
        float scale{std::pow(2.f, this->mScale)};
        return glm::ortho(this->mLeft * scale, this->mRight * scale, this->mBottom * scale, this->mTop * scale, this->mNear, this->mFar);
    }

    void scale(float deltaScale) override;

private:
    float mLeft{-1.f};
    float mRight{1.f};
    float mBottom{-1.f};
    float mTop{1.f};
    float mNear{-1.f};
    float mFar{1.f};
    float mScale{0.f};
};


#endif //OPENGL_ORTHOGRAPHIC_CAMERA_H
