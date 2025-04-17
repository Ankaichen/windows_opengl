/**
  ******************************************************************************
  * @file           : object.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-12
  ******************************************************************************
  */

#include "object.h"

#include <algorithm>

#include "../shader.h"

Object::Object(const glm::vec3 &position, float angleX, float angleY, float angleZ, const glm::vec3 &scale)
        : mPosition{position}, mAngleX{angleX}, mAngleY{angleY}, mAngleZ{angleZ}, mScale{scale} {
}

Object::~Object() noexcept = default;

glm::mat4 Object::getModelMatrix() const {
    auto modelMatrix = glm::identity<glm::mat4>();
    modelMatrix = glm::scale(modelMatrix, this->mScale);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(this->mAngleX), glm::vec3{1.f, 0.f, 0.f});
    modelMatrix = glm::rotate(modelMatrix, glm::radians(this->mAngleY), glm::vec3{0.f, 1.f, 0.f});
    modelMatrix = glm::rotate(modelMatrix, glm::radians(this->mAngleZ), glm::vec3{0.f, 0.f, 1.f});
    modelMatrix = glm::translate(glm::identity<glm::mat4>(), this->mPosition) * modelMatrix;
    std::shared_ptr<Object> parent = this->mParent.lock();
    return ((parent == nullptr) ? glm::identity<glm::mat4>() : parent->getModelMatrix()) * modelMatrix;
}

void Object::addUniformToShader(const std::shared_ptr<Shader> &shader) const {
    shader->setMatrix4x4("modelMatrix", this->getModelMatrix());
    shader->setMatrix3x3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(this->getModelMatrix()))));
}

void Object::addChild(std::shared_ptr<Object> obj) {
    auto iter = std::find(this->mChildren.cbegin(), this->mChildren.cend(), obj);
    if (iter != this->mChildren.cend()) {
        return;
    }
    obj->mParent = this->shared_from_this();
    this->mChildren.emplace_back(std::move(obj));
}
