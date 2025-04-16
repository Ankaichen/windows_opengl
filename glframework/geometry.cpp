/**
  ******************************************************************************
  * @file           : geometry.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-4-10
  ******************************************************************************
  */

#include "geometry.h"

#include "../wrapper/wrapper.h"

Geometry::Geometry(const std::vector<GLfloat> &positions, const std::vector<GLfloat> &normals,
                   const std::vector<GLfloat> &uvs, const std::vector<GLuint> &indices) {
    GL_CALL(glGenVertexArrays(1, &this->mVao));
    GL_CALL(glGenBuffers(1, &this->mPosVbo));
    GL_CALL(glGenBuffers(1, &this->mUvVbo));
    GL_CALL(glGenBuffers(1, &this->mNormalVbo));
    GL_CALL(glGenBuffers(1, &this->mEbo));

    GL_CALL(glBindVertexArray(this->mVao));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, this->mPosVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * positions.size(), positions.data(), GL_STATIC_DRAW));
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<void *>(0)));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, this->mUvVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * uvs.size(), uvs.data(), GL_STATIC_DRAW));
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), reinterpret_cast<void *>(0)));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, this->mNormalVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * normals.size(), normals.data(), GL_STATIC_DRAW));
    GL_CALL(glEnableVertexAttribArray(2));
    GL_CALL(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<void *>(0)));

    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mEbo));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW));

    GL_CALL(glBindVertexArray(0));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    this->mIndicesCount = indices.size();
}

Geometry::~Geometry() noexcept {
    if (this->mVao != 0) { GL_CALL(glDeleteVertexArrays(1, &this->mVao)); }
    if (this->mPosVbo != 0) { GL_CALL(glDeleteBuffers(1, &this->mPosVbo)); }
    if (this->mUvVbo != 0) { GL_CALL(glDeleteBuffers(1, &this->mUvVbo)); }
    if (this->mNormalVbo != 0) { GL_CALL(glDeleteBuffers(1, &this->mNormalVbo)); }
    if (this->mEbo != 0) { GL_CALL(glDeleteBuffers(1, &this->mEbo)); }
}

std::unique_ptr<Geometry> Geometry::createPlane(float width, float height) {
    auto resultGeometry = std::make_unique<Geometry>();
    GLfloat halfWidth = width / 2;
    GLfloat halfHeight = height / 2;
    GLfloat positions[] = {
            /*1*/ -halfWidth, halfHeight, 0, /*2*/ halfWidth, halfHeight, 0,
            /*3*/ halfWidth, -halfHeight, 0, /*4*/ -halfWidth, -halfHeight, 0,
    };
    GLfloat uvs[] = {
            /*1*/ 0.f, 1.f, /*2*/ 1.f, 1.f, /*3*/ 1.f, 0.f, /*4*/ 0.f, 0.f,
    };
    GLfloat normals[]{
            /*1*/ 0.f, 0.f, 1.f, /*2*/ 0.f, 0.f, 1.f,
            /*3*/ 0.f, 0.f, 1.f, /*4*/ 0.f, 0.f, 1.f
    };
    GLuint indices[] = {
            0, 1, 3,
            1, 2, 3
    };
    GL_CALL(glGenVertexArrays(1, &resultGeometry->mVao));
    GL_CALL(glGenBuffers(1, &resultGeometry->mPosVbo));
    GL_CALL(glGenBuffers(1, &resultGeometry->mUvVbo));
    GL_CALL(glGenBuffers(1, &resultGeometry->mNormalVbo));
    GL_CALL(glGenBuffers(1, &resultGeometry->mEbo));

    GL_CALL(glBindVertexArray(resultGeometry->mVao));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, resultGeometry->mPosVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<void *>(0)));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, resultGeometry->mUvVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW));
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), reinterpret_cast<void *>(0)));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, resultGeometry->mNormalVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW));
    GL_CALL(glEnableVertexAttribArray(2));
    GL_CALL(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<void *>(0)));

    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, resultGeometry->mEbo));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    GL_CALL(glBindVertexArray(0));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    resultGeometry->mIndicesCount = sizeof(indices) / sizeof(GLfloat);
    return resultGeometry;
}

std::unique_ptr<Geometry> Geometry::createBox(float size) {
    auto resultGeometry = std::make_unique<Geometry>();
    GLfloat halfSize = size / 2;
    GLfloat positions[] = {
            // plane front
            /*1*/ -halfSize, halfSize, halfSize, /*2*/ halfSize, halfSize, halfSize,
            /*3*/ halfSize, -halfSize, halfSize, /*4*/ -halfSize, -halfSize, halfSize,
            // plane back
            /*1*/ halfSize, halfSize, -halfSize, /*2*/ -halfSize, halfSize, -halfSize,
            /*3*/ -halfSize, -halfSize, -halfSize, /*4*/ halfSize, -halfSize, -halfSize,
            // plane left
            /*1*/ -halfSize, halfSize, -halfSize, /*2*/ -halfSize, halfSize, halfSize,
            /*3*/ -halfSize, -halfSize, halfSize, /*4*/ -halfSize, -halfSize, -halfSize,
            // plane right
            /*1*/ halfSize, halfSize, halfSize, /*2*/ halfSize, halfSize, -halfSize,
            /*3*/ halfSize, -halfSize, -halfSize, /*4*/ halfSize, -halfSize, halfSize,
            // plane bottom
            /*1*/ -halfSize, -halfSize, halfSize, /*2*/ halfSize, -halfSize, halfSize,
            /*3*/ halfSize, -halfSize, -halfSize, /*4*/ -halfSize, -halfSize, -halfSize,
            // plane top
            /*1*/ -halfSize, halfSize, -halfSize, /*2*/ halfSize, halfSize, -halfSize,
            /*3*/ halfSize, halfSize, halfSize, /*4*/ -halfSize, halfSize, halfSize
    };
    GLfloat uvs[] = {
            // plane front
            /*1*/ 0.f, 1.f, /*2*/ 1.f, 1.f, /*3*/ 1.f, 0.f, /*4*/ 0.f, 0.f,
            // plane back
            /*1*/ 0.f, 1.f, /*2*/ 1.f, 1.f, /*3*/ 1.f, 0.f, /*4*/ 0.f, 0.f,
            // plane left
            /*1*/ 0.f, 1.f, /*2*/ 1.f, 1.f, /*3*/ 1.f, 0.f, /*4*/ 0.f, 0.f,
            // plane right
            /*1*/ 0.f, 1.f, /*2*/ 1.f, 1.f, /*3*/ 1.f, 0.f, /*4*/ 0.f, 0.f,
            // plane bottom
            /*1*/ 0.f, 1.f, /*2*/ 1.f, 1.f, /*3*/ 1.f, 0.f, /*4*/ 0.f, 0.f,
            // plane top
            /*1*/ 0.f, 1.f, /*2*/ 1.f, 1.f, /*3*/ 1.f, 0.f, /*4*/ 0.f, 0.f
    };
    GLfloat normals[] = {
            // plane front
            /*1*/ 0.f, 0.f, 1.f, /*2*/ 0.f, 0.f, 1.f,
            /*3*/ 0.f, 0.f, 1.f, /*4*/ 0.f, 0.f, 1.f,
            // plane back
            /*1*/ 0.f, 0.f, -1.f, /*2*/ 0.f, 0.f, -1.f,
            /*3*/ 0.f, 0.f, -1.f, /*4*/ 0.f, 0.f, -1.f,
            // plane left
            /*1*/ -1.f, 0.f, 0.f, /*2*/ -1.f, 0.f, 0.f,
            /*3*/ -1.f, 0.f, 0.f, /*4*/ -1.f, 0.f, 0.f,
            // plane right
            /*1*/ 1.f, 0.f, 0.f, /*2*/ 1.f, 0.f, 0.f,
            /*3*/ 1.f, 0.f, 0.f, /*4*/ 1.f, 0.f, 0.f,
            // plane bottom
            /*1*/ 0.f, -1.f, 0.f, /*2*/ 0.f, -1.f, 0.f,
            /*3*/ 0.f, -1.f, 0.f, /*4*/ 0.f, -1.f, 0.f,
            // plane top
            /*1*/ 0.f, 1.f, 0.f, /*2*/ 0.f, 1.f, 0.f,
            /*3*/ 0.f, 1.f, 0.f, /*4*/ 0.f, 1.f, 0.f
    };
    GLuint indices[] = {
            // plane front
            0, 1, 3, 1, 2, 3,
            // plane back
            4, 5, 7, 5, 6, 7,
            // plane left
            8, 9, 11, 9, 10, 11,
            // plane right
            12, 13, 15, 13, 14, 15,
            // plane bottom
            16, 17, 19, 17, 18, 19,
            // plane top
            20, 21, 23, 21, 22, 23
    };
    GL_CALL(glGenVertexArrays(1, &resultGeometry->mVao));
    GL_CALL(glGenBuffers(1, &resultGeometry->mPosVbo));
    GL_CALL(glGenBuffers(1, &resultGeometry->mUvVbo));
    GL_CALL(glGenBuffers(1, &resultGeometry->mNormalVbo));
    GL_CALL(glGenBuffers(1, &resultGeometry->mEbo));

    GL_CALL(glBindVertexArray(resultGeometry->mVao));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, resultGeometry->mPosVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<void *>(0)));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, resultGeometry->mUvVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW));
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), reinterpret_cast<void *>(0)));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, resultGeometry->mNormalVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW));
    GL_CALL(glEnableVertexAttribArray(2));
    GL_CALL(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<void *>(0)));

    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, resultGeometry->mEbo));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    GL_CALL(glBindVertexArray(0));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    resultGeometry->mIndicesCount = sizeof(indices) / sizeof(GLfloat);

    return resultGeometry;
}

std::unique_ptr<Geometry> Geometry::createSphere(float radius, int numLat, int numLong) {
    auto resultGeometry = std::make_unique<Geometry>();

    // 经度起始点和结束点重合 但是有两个uv坐标
    int vecCount = (numLat + 1) * (numLong + 1);
    int triCount = numLat * numLong * 2;

    std::vector<GLfloat> positions(vecCount * 3, 0.f);
    std::vector<GLfloat> uvs(vecCount * 2, 0.f);
    std::vector<GLfloat> normals(vecCount * 3, 0.f);
    std::vector<GLuint> indices(triCount * 3, 0);

    for (int i = 0; i <= numLat; ++i) {
        for (int j = 0; j <= numLong; ++j) {
            float u = 1 - static_cast<float>(j) / static_cast<float>(numLong),
                    v = 1 - static_cast<float>(i) / static_cast<float>(numLat);
            float psi = (1 - v) * glm::pi<float>();
            float theta = (1 - u) * 2 * glm::pi<float>() - glm::pi<float>();
            int vecIndex = i * (numLong + 1) + j;
            positions[vecIndex * 3 + 0] = radius * glm::sin(psi) * glm::cos(theta); // x
            positions[vecIndex * 3 + 1] = radius * glm::cos(psi);                      // y
            positions[vecIndex * 3 + 2] = radius * glm::sin(psi) * glm::sin(theta); // z
            uvs[vecIndex * 2 + 0] = u;
            uvs[vecIndex * 2 + 1] = v;
            normals[vecIndex * 3 + 0] = positions[vecIndex * 3 + 0];
            normals[vecIndex * 3 + 1] = positions[vecIndex * 3 + 1];
            normals[vecIndex * 3 + 2] = positions[vecIndex * 3 + 2];
        }
    }

    for (int i = 0; i < numLat; ++i) {
        for (int j = 0; j < numLong; ++j) {
            int vecIndex = i * (numLong + 1) + j;
            int indIndex = (i * numLong + j) * 6;
            indices[indIndex + 0] = vecIndex;
            indices[indIndex + 1] = vecIndex + numLong + 2;
            indices[indIndex + 2] = vecIndex + numLong + 1;

            indices[indIndex + 3] = vecIndex;
            indices[indIndex + 4] = vecIndex + 1;
            indices[indIndex + 5] = vecIndex + numLong + 2;
        }
    }

    GL_CALL(glGenVertexArrays(1, &resultGeometry->mVao));
    GL_CALL(glGenBuffers(1, &resultGeometry->mPosVbo));
    GL_CALL(glGenBuffers(1, &resultGeometry->mUvVbo));
    GL_CALL(glGenBuffers(1, &resultGeometry->mNormalVbo));
    GL_CALL(glGenBuffers(1, &resultGeometry->mEbo));

    GL_CALL(glBindVertexArray(resultGeometry->mVao));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, resultGeometry->mPosVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * positions.size(), positions.data(), GL_STATIC_DRAW));
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<void *>(0)));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, resultGeometry->mUvVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * uvs.size(), uvs.data(), GL_STATIC_DRAW));
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), reinterpret_cast<void *>(0)));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, resultGeometry->mNormalVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * normals.size(), normals.data(), GL_STATIC_DRAW));
    GL_CALL(glEnableVertexAttribArray(2));
    GL_CALL(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<void *>(0)));

    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, resultGeometry->mEbo));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW));

    GL_CALL(glBindVertexArray(0));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    resultGeometry->mIndicesCount = indices.size();

    return std::move(resultGeometry);
}


