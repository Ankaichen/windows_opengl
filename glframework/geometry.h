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
#include <vector>

#include "core.h"

class Geometry {

public:
    Geometry() = default;

    Geometry(
            const std::vector<GLfloat> &positions,
            const std::vector<GLfloat> &normals,
            const std::vector<GLfloat> &uvs,
            const std::vector<GLuint> &indices
    );

    ~Geometry() noexcept;

    [[nodiscard]] inline GLuint getVao() const { return this->mVao; }

    [[nodiscard]] inline GLuint getEbo() const { return this->mEbo; }

    [[nodiscard]] inline uint32_t getIndicesCount() const { return this->mIndicesCount; }

    static std::unique_ptr<Geometry> createPlane(float width, float height);

    static std::unique_ptr<Geometry> createBox(float size);

    static std::unique_ptr<Geometry> createSphere(float radius, int numLat = 60, int numLong = 60);

private:
    GLuint mVao{0};
    GLuint mPosVbo{0};
    GLuint mUvVbo{0};
    GLuint mNormalVbo{0};
    GLuint mEbo{0};

    uint32_t mIndicesCount{0};
};


#endif //OPENGL_GEOMETRY_H
