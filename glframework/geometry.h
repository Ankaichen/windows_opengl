/**
  ******************************************************************************
  * @file           : geometry.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-4-10
  ******************************************************************************
  */

#ifndef OPENGL_GEOMETRY_H
#define OPENGL_GEOMETRY_H

#include <memory>

#include "core.h"

class Geometry {

public:
    Geometry() = default;

    ~Geometry();

    inline GLuint getVao() const { return this->mVao; }
    inline GLuint getEbo() const { return this->mEbo; }
    inline uint32_t getIndicesCount() const { return this->mIndicesCount; }

    static std::unique_ptr<Geometry> createBox(float size);

    static std::unique_ptr<Geometry> createSphere(float radius, int num_lat = 60, int num_long = 60);

private:
    GLuint mVao{0};
    GLuint mPosVbo{0};
    GLuint mUvVbo{0};
    GLuint mEbo{0};

    uint32_t mIndicesCount{0};
};


#endif //OPENGL_GEOMETRY_H
