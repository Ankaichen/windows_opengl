/**
  ******************************************************************************
  * @file           : render_able.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-4-17
  ******************************************************************************
  */

#ifndef OPENGL_RENDER_ABLE_H
#define OPENGL_RENDER_ABLE_H

#include "../core.h"

enum class MaterialType;

struct RenderData {
    GLuint vao;
    GLuint indicesCount;
    bool enable;
    MaterialType materialType;
};

class Renderable {
public:
    Renderable() = default;

    virtual ~Renderable() = 0;

    virtual const RenderData getRenderData() const { return {.enable = false}; }
};


#endif //OPENGL_RENDER_ABLE_H
