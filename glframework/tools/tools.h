/**
  ******************************************************************************
  * @file           : tools.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-16
  ******************************************************************************
  */

#ifndef OPENGL_TOOLS_H
#define OPENGL_TOOLS_H

#include "../core.h"

class Tools {
public:
    /**
     * 结构输入矩阵的位置、旋转、缩放信息
     * @param matrix
     * @param position
     * @param angles 欧拉角
     * @param scale
     */
    static void decompose(const glm::mat4 &matrix, glm::vec3 &position, glm::vec3 &angles, glm::vec3 scale);
};


#endif //OPENGL_TOOLS_H
