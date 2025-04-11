/**
  ******************************************************************************
  * @file           : shader.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-3-16
  ******************************************************************************
  */

#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include "core.h"

#include <string_view>

class Shader {
public:
    Shader(const char *vertexPath, const char *fragmentPath);

    ~Shader();

    void begin();

    void end();

    void setFloat(std::string_view name, GLfloat value) const;
    void setVec3f(std::string_view name, GLfloat value0, GLfloat value1, GLfloat value2) const;
    void setVec3f(std::string_view name, const GLfloat *values) const;
    void setInt(std::string_view name, GLint value) const;
    void setMatrix4x4(std::string_view name, glm::mat4 value) const;

private:
    void checkShaderErrors(GLuint target, GLenum type) const;

private:
    GLuint mProgram{0};
    bool mIsUsing{false};
};

#endif //OPENGL_SHADER_H
