/**
  ******************************************************************************
  * @file           : texture.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-4-1
  ******************************************************************************
  */

#include "texture.h"

#include "../wrapper/wrapper.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

#include <iostream>

Texture::Texture(std::string_view filename, GLuint unit) : mUnit(unit) {
    // stb image 读取图片
    int channels;
    // 反转y轴
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filename.data(), &(this->mWidth), &(this->mHeight), &channels, STBI_rgb_alpha);
    // 生成纹理并激活单元绑定
    GL_CALL(glGenTextures(1, &(this->mTexture)));
    // 激活纹理单元
    GL_CALL(glActiveTexture(GL_TEXTURE0 + this->mUnit));
    // 绑定纹理对象
    GL_CALL(glBindTexture(GL_TEXTURE_2D, this->mTexture));
    // 自动生成mipmap
    GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->mWidth, this->mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
    GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));
    // 释放数据
    stbi_image_free(data);
    // 设置纹理的过滤方式
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    // 设置纹理的包裹方式
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)); // U
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)); // V
}

Texture::~Texture() noexcept {
    if (this->mTexture != 0) {
        GL_CALL(glDeleteTextures(1, &(this->mTexture)));
    }
}

void Texture::bind() const {
    // 先切换纹理单元
    GL_CALL(glActiveTexture(GL_TEXTURE0 + this->mUnit));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, this->mTexture));
}
