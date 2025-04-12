/**
  ******************************************************************************
  * @file           : texture.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-4-1
  ******************************************************************************
  */

#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

#include "core.h"
#include <string_view>

class Texture {
public:
    Texture(std::string_view filename, GLuint unit);

    ~Texture() noexcept;

    [[nodiscard]] inline int getWidth() const { return this->mWidth; }

    [[nodiscard]] inline int getHeight() const { return this->mHeight; }

    [[nodiscard]] inline GLuint getUnit() const { return this->mUnit; }

    void bind() const;

private:
    int mWidth{0};
    int mHeight{0};
    GLuint mUnit{0};
    GLuint mTexture{0};
};


#endif //OPENGL_TEXTURE_H
