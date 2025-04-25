/**
  ******************************************************************************
  * @file           : material.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-12
  ******************************************************************************
  */

#include "material.h"

Material::Material(MaterialType materialType) : mMaterialType(materialType) {
}

Material::~Material() noexcept = default;

void Material::bind() const {
    if (this->mDepthTest) {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(this->mDepthFunc);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
    if (this->mDepthWrite) {
        glDepthMask(GL_TRUE);
    } else {
        glDepthMask(GL_FALSE);
    }
    if (this->mPolygonOffset) {
        glEnable(this->mPolygonOffsetType);
        glPolygonOffset(this->mFactor, this->mUnit);
    } else {
        glDisable(GL_POLYGON_OFFSET_FILL);
        glDisable(GL_POLYGON_OFFSET_LINE);
    }
    if (this->mStencilTest) {
        glEnable(GL_STENCIL_TEST);
        glStencilOp(this->mFail, this->mZFail, this->mZPass);
        glStencilFunc(this->mStencilFunc, this->mStencilRef, this->mStencilFuncMask);
        glStencilMask(this->mStencilMask);
    } else {
        glDisable(GL_STENCIL_TEST);
    }
}
