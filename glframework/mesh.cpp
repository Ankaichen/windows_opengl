/**
  ******************************************************************************
  * @file           : mesh.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-12
  ******************************************************************************
  */

#include "mesh.h"

Mesh::Mesh(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material)
        : Object(), mGeometry(std::move(geometry)), mMaterial(std::move(material)) {
}

Mesh::~Mesh() noexcept {

}
