/**
  ******************************************************************************
  * @file           : object.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-12
  ******************************************************************************
  */

#ifndef OPENGL_OBJECT_H
#define OPENGL_OBJECT_H

#include <memory>
#include <vector>

#include "../core.h"
#include "../shader_uniformer.h"

class Object : virtual public ShaderUniformer, public std::enable_shared_from_this<Object> {
public:
    Object() = default;

    Object(const glm::vec3 &position, float angleX, float angleY, float angleZ, const glm::vec3 &scale);

    virtual ~Object() noexcept = 0;

    inline void setPosition(const glm::vec3 &position) { this->mPosition = position; }

    inline void rotateX(float angle) { this->mAngleX += angle; }

    inline void rotateY(float angle) { this->mAngleY += angle; }

    inline void rotateZ(float angle) { this->mAngleZ += angle; }

    inline void setAngleX(float angle) { this->mAngleX = angle; }

    inline void setAngleY(float angle) { this->mAngleY = angle; }

    inline void setAngleZ(float angle) { this->mAngleZ = angle; }

    inline void setScale(const glm::vec3 &scale) { this->mScale = scale; }

    [[nodiscard]] inline glm::vec3 getPosition() const { return this->mPosition; }

    [[nodiscard]] glm::mat4 getModelMatrix() const;

    void addUniformToShader(const std::shared_ptr<Shader> &shader) const override;

    void addChild(std::shared_ptr<Object> obj);

    std::vector<std::shared_ptr<Object>> getChildren() const { return this->mChildren; };

    std::shared_ptr<Object> getParent() const { return this->mParent.lock(); }

protected:
    glm::vec3 mPosition{0.f};
    // 旋转顺序 pitch(x) -> yaw(y) -> roll(z)
    float mAngleX{0.f}, mAngleY{0.f}, mAngleZ{0.f};

    glm::vec3 mScale{1.f};

    std::vector<std::shared_ptr<Object>> mChildren{};
    std::weak_ptr<Object> mParent{};
};


#endif //OPENGL_OBJECT_H
