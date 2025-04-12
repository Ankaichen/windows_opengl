/**
  ******************************************************************************
  * @file           : wrapper.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-3-13
  ******************************************************************************
  */

#include "wrapper.h"

#include <sstream>
#include <iostream>
#include "glad/glad.h"

bool glCheckError() {
    GLenum errorCode = glGetError();
    if (errorCode != GL_NO_ERROR) {
        std::stringstream ss;
        ss << "error " << errorCode;
        switch (errorCode) {
            case GL_INVALID_ENUM:
                ss << ": invalid enum";
                break;
            case GL_INVALID_VALUE:
                ss << ": invalid value";
                break;
            case GL_INVALID_OPERATION:
                ss << ": invalid operation";
                break;
            case GL_STACK_OVERFLOW:
                ss << ": stack overflow";
                break;
            case GL_STACK_UNDERFLOW:
                ss << ": stack underflow";
                break;
            case GL_OUT_OF_MEMORY:
                ss << ": out of memory";
                break;
            default:
                ss << ": unknown error";
                break;
        }
        std::cerr << ss.str() << std::endl;
        return false;
    }
    return true;
}
