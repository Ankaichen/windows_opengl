/**
  ******************************************************************************
  * @file           : renderer.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-12
  ******************************************************************************
  */

#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include <vector>
#include <memory>
#include <map>
#include <string_view>

class Mesh;

class Camera;

class DirectionalLight;

class AmbientLight;

class Shader;

enum class MaterialType;

class Material;

class Renderer {
public:
    Renderer() = default;

    ~Renderer() noexcept;

    void addShader(MaterialType materialType, std::string_view vertexPath, std::string_view fragmentPath);

    /**
     * 渲染一帧
     */
    void render(
            const std::vector<std::shared_ptr<Mesh>> &meshes,
            const std::shared_ptr<Camera> &camera,
            const std::shared_ptr<DirectionalLight> &directionalLight,
            const std::shared_ptr<AmbientLight> &ambientLight
    );

private:
    std::map<MaterialType, std::shared_ptr<Shader>> mShaders{};
};


#endif //OPENGL_RENDERER_H
