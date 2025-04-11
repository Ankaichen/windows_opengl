/**
  ******************************************************************************
  * @file           : camera.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-4-9
  ******************************************************************************
  */

#ifndef OPENGL_CAMERA_H
#define OPENGL_CAMERA_H

#include <iostream>

#include "../../glframework/core.h"

class Camera {

public:

    Camera() = default;

    Camera(const glm::vec3 &position, const glm::vec3 &up_vec, const glm::vec3 &right_vec);

    virtual ~Camera() = 0;

    inline glm::vec3 getPosition() const { return this->mPosition; }

    inline void setPosition(const glm::vec3 &position) { this->mPosition = position; }

    inline glm::vec3 getUpVec() const { return this->mUpVec; }

    inline void setUpVec(const glm::vec3 &up_vec) { this->mUpVec = up_vec; }

    inline glm::vec3 getRightVec() const { return this->mRightVec; }

    inline void setRightVec(const glm::vec3 &right_vec) { this->mRightVec = right_vec; }

    inline glm::mat4 getViewMatrix() const {
        return glm::lookAt(this->mPosition, glm::cross(this->mUpVec, this->mRightVec) + this->mPosition, this->mUpVec);
    };

    virtual inline glm::mat4 getProjectionMatrix() const = 0;

    virtual inline void scale(float delta_scale) = 0;

protected:
    glm::vec3 mPosition{0.f, 0.f, 1.f};
    glm::vec3 mUpVec{0.f, 1.f, 0.f};
    glm::vec3 mRightVec{1.f, 0.f, 0.f};

};


#endif //OPENGL_CAMERA_H
