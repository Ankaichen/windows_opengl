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

#include <vector>
#include <memory>

#include "../wrapper/wrapper.h"

Geometry::~Geometry() {
    if (this->mVao != 0) glDeleteVertexArrays(1, &this->mVao);
    if (this->mPosVbo != 0) glDeleteBuffers(1, &this->mPosVbo);
    if (this->mUvVbo != 0) glDeleteBuffers(1, &this->mUvVbo);
    if (this->mNormalVbo != 0) glDeleteBuffers(1, &this->mNormalVbo);
    if (this->mEbo != 0) glDeleteBuffers(1, &this->mEbo);
}

std::unique_ptr<Geometry> Geometry::createPlane(float width, float height) {
    auto res_geo = std::make_unique<Geometry>();
    GLfloat half_width = width / 2;
    GLfloat half_height = height / 2;
    GLfloat positions[] = {
            /*1*/ -half_width, half_height, 0, /*2*/ half_width, half_height, 0,
            /*3*/ half_width, -half_height, 0, /*4*/ -half_width, -half_height, 0,
    };
    GLfloat uvs[] = {
            /*1*/ 0.f, 1.f, /*2*/ 1.f, 1.f, /*3*/ 1.f, 0.f, /*4*/ 0.f, 0.f,
    };
    GLfloat normals[] {
            /*1*/ 0.f, 0.f, 1.f, /*2*/ 0.f, 0.f, 1.f,
            /*3*/ 0.f, 0.f, 1.f, /*4*/ 0.f, 0.f, 1.f
    };
    GLuint indices[] = {
            0, 1, 3,
            1, 2, 3
    };
    GL_CALL(glGenVertexArrays(1, &res_geo->mVao));
    GL_CALL(glGenBuffers(1, &res_geo->mPosVbo));
    GL_CALL(glGenBuffers(1, &res_geo->mUvVbo));
    GL_CALL(glGenBuffers(1, &res_geo->mNormalVbo));
    GL_CALL(glGenBuffers(1, &res_geo->mEbo));

    GL_CALL(glBindVertexArray(res_geo->mVao));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, res_geo->mPosVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<void *>(0)));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, res_geo->mUvVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW));
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), reinterpret_cast<void *>(0)));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, res_geo->mNormalVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW));
    GL_CALL(glEnableVertexAttribArray(2));
    GL_CALL(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<void *>(0)));

    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, res_geo->mEbo));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    GL_CALL(glBindVertexArray(0));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    res_geo->mIndicesCount = sizeof(indices) / sizeof(GLfloat);
    return res_geo;
}

std::unique_ptr<Geometry> Geometry::createBox(float size) {
    auto res_geo = std::make_unique<Geometry>();
    GLfloat half_size = size / 2;
    GLfloat positions[] = {
            // plane front
            /*1*/ -half_size, half_size, half_size, /*2*/ half_size, half_size, half_size,
            /*3*/ half_size, -half_size, half_size, /*4*/ -half_size, -half_size, half_size,
            // plane back
            /*1*/ half_size, half_size, -half_size, /*2*/ -half_size, half_size, -half_size,
            /*3*/ -half_size, -half_size, -half_size, /*4*/ half_size, -half_size, -half_size,
            // plane left
            /*1*/ -half_size, half_size, -half_size, /*2*/ -half_size, half_size, half_size,
            /*3*/ -half_size, -half_size, half_size, /*4*/ -half_size, -half_size, -half_size,
            // plane right
            /*1*/ half_size, half_size, half_size, /*2*/ half_size, half_size, -half_size,
            /*3*/ half_size, -half_size, -half_size, /*4*/ half_size, -half_size, half_size,
            // plane bottom
            /*1*/ -half_size, -half_size, half_size, /*2*/ half_size, -half_size, half_size,
            /*3*/ half_size, -half_size, -half_size, /*4*/ -half_size, -half_size, -half_size,
            // plane top
            /*1*/ -half_size, half_size, -half_size, /*2*/ half_size, half_size, -half_size,
            /*3*/ half_size, half_size, half_size, /*4*/ -half_size, half_size, half_size
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
    GL_CALL(glGenVertexArrays(1, &res_geo->mVao));
    GL_CALL(glGenBuffers(1, &res_geo->mPosVbo));
    GL_CALL(glGenBuffers(1, &res_geo->mUvVbo));
    GL_CALL(glGenBuffers(1, &res_geo->mNormalVbo));
    GL_CALL(glGenBuffers(1, &res_geo->mEbo));

    GL_CALL(glBindVertexArray(res_geo->mVao));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, res_geo->mPosVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<void *>(0)));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, res_geo->mUvVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW));
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), reinterpret_cast<void *>(0)));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, res_geo->mNormalVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW));
    GL_CALL(glEnableVertexAttribArray(2));
    GL_CALL(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<void *>(0)));

    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, res_geo->mEbo));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    GL_CALL(glBindVertexArray(0));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    res_geo->mIndicesCount = sizeof(indices) / sizeof(GLfloat);

    return std::move(res_geo);
}

std::unique_ptr<Geometry> Geometry::createSphere(float radius, int num_lat, int num_long) {
    auto res_geo = std::make_unique<Geometry>();

    // 经度起始点和结束点重合 但是有两个uv坐标
    int vec_count = (num_lat + 1) * (num_long + 1);
    int tri_count = num_lat * num_long * 2;

    std::vector<GLfloat> positions(vec_count * 3, 0.f);
    std::vector<GLfloat> uvs(vec_count * 2, 0.f);
    std::vector<GLfloat> normals(vec_count * 3, 0.f);
    std::vector<GLuint> indices(tri_count * 3, 0);

    for (int i = 0; i <= num_lat; ++i) {
        for (int j = 0; j <= num_long; ++j) {
            float u = 1 - static_cast<float>(j) / static_cast<float>(num_long),
                    v = 1 - static_cast<float>(i) / static_cast<float>(num_lat);
            float psi = (1 - v) * glm::pi<float>();
            float theta = (1 - u) * 2 * glm::pi<float>() - glm::pi<float>();
            int vec_index = i * (num_long + 1) + j;
            positions[vec_index * 3 + 0] = radius * glm::sin(psi) * glm::cos(theta); // x
            positions[vec_index * 3 + 1] = radius * glm::cos(psi);                      // y
            positions[vec_index * 3 + 2] = radius * glm::sin(psi) * glm::sin(theta); // z
            uvs[vec_index * 2 + 0] = u;
            uvs[vec_index * 2 + 1] = v;
            normals[vec_index * 3 + 0] = positions[vec_index * 3 + 0];
            normals[vec_index * 3 + 1] = positions[vec_index * 3 + 1];
            normals[vec_index * 3 + 2] = positions[vec_index * 3 + 2];
        }
    }

    for (int i = 0; i < num_lat; ++i) {
        for (int j = 0; j < num_long; ++j) {
            int vec_index = i * (num_long + 1) + j;
            int ind_index = (i * num_long + j) * 6;
            indices[ind_index + 0] = vec_index;
            indices[ind_index + 1] = vec_index + num_long + 2;
            indices[ind_index + 2] = vec_index + num_long + 1;

            indices[ind_index + 3] = vec_index;
            indices[ind_index + 4] = vec_index + 1;
            indices[ind_index + 5] = vec_index + num_long + 2;
        }
    }

    GL_CALL(glGenVertexArrays(1, &res_geo->mVao));
    GL_CALL(glGenBuffers(1, &res_geo->mPosVbo));
    GL_CALL(glGenBuffers(1, &res_geo->mUvVbo));
    GL_CALL(glGenBuffers(1, &res_geo->mNormalVbo));
    GL_CALL(glGenBuffers(1, &res_geo->mEbo));

    GL_CALL(glBindVertexArray(res_geo->mVao));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, res_geo->mPosVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * positions.size(), positions.data(), GL_STATIC_DRAW));
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<void *>(0)));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, res_geo->mUvVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * uvs.size(), uvs.data(), GL_STATIC_DRAW));
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), reinterpret_cast<void *>(0)));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, res_geo->mNormalVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * normals.size(), normals.data(), GL_STATIC_DRAW));
    GL_CALL(glEnableVertexAttribArray(2));
    GL_CALL(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<void *>(0)));

    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, res_geo->mEbo));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW));

    GL_CALL(glBindVertexArray(0));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    res_geo->mIndicesCount = indices.size();

    return std::move(res_geo);
}


