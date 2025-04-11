/**
  ******************************************************************************
  * @file           : wrapper.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-3-13
  ******************************************************************************
  */

#ifndef OPENGL_WRAPPER_H
#define OPENGL_WRAPPER_H

#ifdef DEBUG
#include <cassert>
#define GL_CALL(func) func; assert(glCheckError())
#else
#define GL_CALL(func) func
#endif

bool glCheckError();

#endif //OPENGL_WRAPPER_H
