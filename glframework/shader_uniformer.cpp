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

#include "shader.h"

ShaderUniformer::~ShaderUniformer() = default;

Shader &operator<<(Shader &shader, const ShaderUniformer &shaderUniformer) {
    shaderUniformer.addUniformToShader(shader);
    return shader;
}
