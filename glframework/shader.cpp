/**
  ******************************************************************************
  * @file           : shader.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-3-16
  ******************************************************************************
  */

#include "shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../wrapper/wrapper.h"

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
    std::string vertexCode, fragmentCode;
    std::ifstream vertexFile, fragmentFile;
    // 保证ifstream遇到问题的时候可以抛出异常
    vertexFile.exceptions(std::ios::failbit | std::ios::badbit);
    fragmentFile.exceptions(std::ios::failbit | std::ios::badbit);
    try { // 读取shader源代码
        vertexFile.open(vertexPath, std::ios::in);
        fragmentFile.open(fragmentPath, std::ios::in);

        std::stringstream vertexStream, fragmentStream;
        vertexStream << vertexFile.rdbuf();
        fragmentStream << fragmentFile.rdbuf();

        vertexFile.close();
        fragmentFile.close();

        vertexCode = vertexStream.str();
        fragmentCode = fragmentStream.str();
    } catch (std::ifstream::failure &e) {
        std::cerr << "Error: Shader file error: " << e.what() << std::endl;
    }
    const char *vertexCodeChar = vertexCode.c_str();
    const char *fragmentCodeChar = fragmentCode.c_str();
    // 创建shader
    GL_CALL(GLuint vertexShader{glCreateShader(GL_VERTEX_SHADER)});
    GL_CALL(GLuint fragmentShader{glCreateShader(GL_FRAGMENT_SHADER)});
    // 导入源代码
    GL_CALL(glShaderSource(vertexShader, 1, &vertexCodeChar, nullptr));
    GL_CALL(glShaderSource(fragmentShader, 1, &fragmentCodeChar, nullptr));
    // 编译shader
    GL_CALL(glCompileShader(vertexShader));
    this->checkShaderErrors(vertexShader, GL_COMPILE_STATUS);
    GL_CALL(glCompileShader(fragmentShader));
    this->checkShaderErrors(fragmentShader, GL_COMPILE_STATUS);
    // 创建program
    GL_CALL(this->mProgram = glCreateProgram());
    // 链接
    GL_CALL(glAttachShader(this->mProgram, vertexShader));
    GL_CALL(glAttachShader(this->mProgram, fragmentShader));
    GL_CALL(glLinkProgram(this->mProgram));
    this->checkShaderErrors(this->mProgram, GL_LINK_STATUS);
    // 删除shader
    GL_CALL(glDeleteShader(vertexShader));
    GL_CALL(glDeleteShader(fragmentShader));

}

Shader::~Shader() {
}

void Shader::begin() {
    GL_CALL(glUseProgram(this->mProgram));
    this->mIsUsing = true;
}

void Shader::end() {
    GL_CALL(glUseProgram(0));
    this->mIsUsing = false;
}

void Shader::checkShaderErrors(GLuint target, GLenum type) const {
    int success{0};
    char infoLog[1024];
    switch (type) {
        case GL_COMPILE_STATUS: {
            GL_CALL(glGetShaderiv(target, type, &success));
            if (!success) {
                GL_CALL(glGetShaderInfoLog(target, 1024, nullptr, infoLog));
                std::cerr << "Error: Shader compile error\n" << infoLog << std::endl;
            }
            break;
        }
        case GL_LINK_STATUS: {
            GL_CALL(glGetProgramiv(target, type, &success));
            if (!success) {
                GL_CALL(glGetProgramInfoLog(target, 1024, nullptr, infoLog));
                std::cerr << "Error: Shader link error\n" << infoLog << std::endl;
            }
            break;
        }
        default:
            std::cerr << "Error: Check shader errors Type is wrong" << std::endl;
            break;
    }
}

void Shader::setFloat(std::string_view name, GLfloat value) const {
    // 通过名称拿到Uniform变量的位置
    GL_CALL(GLint location{glGetUniformLocation(this->mProgram, name.data())});
    // 通过位置更新Uniform变量的值
    GL_CALL(glUniform1f(location, value));
}

void Shader::setVec3f(std::string_view name, GLfloat value0, GLfloat value1, GLfloat value2) const {
    GL_CALL(GLint location{glGetUniformLocation(this->mProgram, name.data())});
    GL_CALL(glUniform3f(location, value0, value1, value2));
}

void Shader::setVec3f(std::string_view name, const GLfloat *values) const {
    GL_CALL(GLint location{glGetUniformLocation(this->mProgram, name.data())});
    // 第二个参数：你当前要更新的uniform变量如果是数组，数组里面包括多少个向量vec3
    GL_CALL(glUniform3fv(location, 1, values));
}

void Shader::setInt(std::string_view name, GLint value) const {
    GL_CALL(GLint location{glGetUniformLocation(this->mProgram, name.data())});
    GL_CALL(glUniform1i(location, value));
}

void Shader::setMatrix4x4(std::string_view name, glm::mat4 value) const {
    GL_CALL(GLint location{glGetUniformLocation(this->mProgram, name.data())});
    GL_CALL(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value)));
}
