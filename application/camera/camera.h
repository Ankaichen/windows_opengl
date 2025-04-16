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
#include "../../glframework/shader_uniformer.h"

class Camera : public ShaderUniformer {

public:

    Camera() = default;

    Camera(const glm::vec3 &position, const glm::vec3 &upVec, const glm::vec3 &rightVec);

    virtual ~Camera() noexcept = 0;

    [[nodiscard]] inline glm::vec3 getPosition() const { return this->mPosition; }

    inline void setPosition(const glm::vec3 &position) { this->mPosition = position; }

    [[nodiscard]] inline glm::vec3 getUpVec() const { return this->mUpVec; }

    inline void setUpVec(const glm::vec3 &upVec) { this->mUpVec = upVec; }

    [[nodiscard]] inline glm::vec3 getRightVec() const { return this->mRightVec; }

    inline void setRightVec(const glm::vec3 &rightVec) { this->mRightVec = rightVec; }

    [[nodiscard]] inline glm::mat4 getViewMatrix() const {
        return glm::lookAt(this->mPosition, glm::cross(this->mUpVec, this->mRightVec) + this->mPosition, this->mUpVec);
    };

    [[nodiscard]] virtual inline glm::mat4 getProjectionMatrix() const = 0;

    virtual inline void scale(float deltaScale) = 0;

    void addUniformToShader(const std::shared_ptr<Shader> &shader) const override;

protected:
    glm::vec3 mPosition{0.f, 0.f, 1.f};
    glm::vec3 mUpVec{0.f, 1.f, 0.f};
    glm::vec3 mRightVec{1.f, 0.f, 0.f};

};


#endif //OPENGL_CAMERA_H
