/**
  ******************************************************************************
  * @file           : shader_uniformer.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-12
  ******************************************************************************
  */

#include "shader_uniformer.h"

#include "../shader.h"

ShaderUniformer::~ShaderUniformer() = default;

std::shared_ptr<Shader> operator<<(const std::shared_ptr<Shader> &shader, const std::shared_ptr<const ShaderUniformer> &shaderUniformer) {
    shaderUniformer->addUniformToShader(shader);
    return std::move(shader);
}
