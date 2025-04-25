/**
  ******************************************************************************
  * @file           : material.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-12
  ******************************************************************************
  */

#ifndef OPENGL_MATERIAL_H
#define OPENGL_MATERIAL_H

#include "../core.h"
#include "../interface/shader_uniformer.h"

enum class MaterialType {
    PHONG_MATERIAL, LIGHT_MATERIAL, DEPTH_MATERIAL
};

class Material : public ShaderUniformer {
public:
public:
    explicit Material(MaterialType materialType);

    ~Material() noexcept override = 0;

    virtual void bind() const;

    [[nodiscard]] inline MaterialType getMaterialType() const { return this->mMaterialType; }

    void setDepthTest(bool depthTest) { this->mDepthTest = depthTest; }

    void setDepthFunc(GLenum depthFunc) { this->mDepthFunc = depthFunc; }

    void setDepthWrite(bool depthWrite) { this->mDepthWrite = depthWrite; }

    void setPolygonOffset(bool polygonOffset) { this->mPolygonOffset = polygonOffset; }

    void setPolygonOffsetType(GLenum polygonOffsetType) { this->mPolygonOffsetType = polygonOffsetType; }

    void setPolygonOffsetParameters(float factor, float unit) {
        this->mFactor = factor;
        this->mUnit = unit;
    }

    void setStencilTest(bool stencilTest) { this->mStencilTest = stencilTest; }

    void setStencilOp(GLenum fail, GLenum zfail, GLenum zpass) {
        this->mFail = fail;
        this->mZFail = zfail;
        this->mZPass = zpass;
    }

    void setStencilMask(GLuint stencilMask) { this->mStencilMask = stencilMask; }

    void setStencilFunc(GLenum stencilFunc) { this->mStencilFunc = stencilFunc; }

    void setStencilRef(GLuint stencilRef) { this->mStencilRef = stencilRef; }

    void setStencilFuncMask(GLuint stencilFuncMask) { this->mStencilFuncMask = stencilFuncMask; }

protected:
    const MaterialType mMaterialType{};
    // 深度检测
    bool mDepthTest{true};
    GLenum mDepthFunc{GL_LESS};
    bool mDepthWrite{true};
    // polygon offset
    bool mPolygonOffset{false};
    GLenum mPolygonOffsetType{GL_POLYGON_OFFSET_FILL};
    float mFactor{0.f};
    float mUnit{0.f};
    // stencil
    bool mStencilTest{true};
    GLenum mFail{GL_KEEP}, mZFail{GL_KEEP}, mZPass{GL_KEEP};
    GLuint mStencilMask{0xff};
    GLenum mStencilFunc{GL_ALWAYS};
    GLuint mStencilRef{0};
    GLuint mStencilFuncMask{0xff};
};


#endif //OPENGL_MATERIAL_H
