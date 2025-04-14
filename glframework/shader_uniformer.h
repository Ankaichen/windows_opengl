/**
  ******************************************************************************
  * @file           : shader_uniformer.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-12
  ******************************************************************************
  */

#ifndef OPENGL_SHADER_UNIFORMER_H
#define OPENGL_SHADER_UNIFORMER_H

#include <map>
#include <string>

class Shader;

class ShaderUniformer {
public:
    friend Shader &operator<<(Shader &shader, const ShaderUniformer &shaderUniformer);

public:
    ShaderUniformer() = default;

    virtual ~ShaderUniformer() = 0;

protected:
    virtual void addUniformToShader(Shader &shader) const = 0;
};


#endif //OPENGL_SHADER_UNIFORMER_H
