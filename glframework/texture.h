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

#include <string_view>
#include <string>
#include <memory>
#include <map>

#include "core.h"

class Texture {
public:
    Texture(std::string_view filePath, GLuint unit);

    Texture(int width, int height, unsigned char *data, GLuint unit);

    ~Texture() noexcept;

    [[nodiscard]] inline int getWidth() const { return this->mWidth; }

    [[nodiscard]] inline int getHeight() const { return this->mHeight; }

    [[nodiscard]] inline GLuint getUnit() const { return this->mUnit; }

    void bind() const;

    static std::shared_ptr<Texture> createTexture(std::string_view filePath, GLuint unit);

    static std::shared_ptr<Texture>
    createTexture(std::string_view filePath, int width, int height, unsigned char *data, GLuint unit);

private:
    int mWidth{0};
    int mHeight{0};
    GLuint mUnit{0};
    GLuint mTexture{0};

    static std::map<std::string, std::weak_ptr<Texture>> textureCache;
};


#endif //OPENGL_TEXTURE_H
