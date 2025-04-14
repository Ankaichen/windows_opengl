#include <iostream>
#include <ctime>
#include <format>
#include <memory>

#include "glframework/core.h"
#include "glframework/shader.h"
#include "glframework/texture.h"
#include "wrapper/wrapper.h"
#include "application/application.h"
#include "application/camera/orthographic_camera.h"
#include "application/camera/perspective_camera.h"
#include "application/camera/track_ball_controller.h"
#include "application/camera/game_camera_controller.h"
#include "glframework/geometry.h"
#include "glframework/mesh.h"
#include "glframework/renderer/renderer.h"
#include "glframework/material/phong_material.h"
#include "glframework/material/white_material.h"
#include "glframework/light/directional_light.h"
#include "glframework/light/ambient_light.h"
#include "glframework/light/point_light.h"

std::vector<std::shared_ptr<Mesh>> meshes{};
std::shared_ptr<Camera> camera{nullptr};
std::unique_ptr<CameraController> cameraController{nullptr};
//std::shared_ptr<DirectionalLight> directionalLight{nullptr};
std::shared_ptr<PointLight> pointLight{nullptr};
std::shared_ptr<AmbientLight> ambientLight{nullptr};
std::unique_ptr<Renderer> renderer{};


void setCallback() {
    // 窗口大小调整的回调函数
    app.setResizeCallback([](int width, int height) -> void {
        GL_CALL(glViewport(0, 0, width, height));
    });

    app.setKeyCallback([](int key, int scancode, int action, int mods) -> void {
        if (cameraController != nullptr) {
            cameraController->onKey(key, action, mods);
        }
    });

    app.setMouseButtonCallback([](int button, int action, int mods) -> void {
        if (cameraController != nullptr) {
            double xpos, ypos;
            app.getCursorPosition(xpos, ypos);
            cameraController->onMouse(button, action, xpos, ypos);
        }
    });

    app.setCursorPosCallback([](double xpos, double ypos) -> void {
        if (cameraController != nullptr) {
            cameraController->onCurse(xpos, ypos);
        }
    });

    app.setScrollCallback([](double xoffset, double yoffset) -> void {
        if (cameraController != nullptr) {
            cameraController->onScroll(static_cast<float>(yoffset));
        }
    });
}

void doTransform() {
//    meshes[1]->rotateY(1.f);
//    meshes[1]->setPosition(
//            glm::rotate(glm::identity<glm::mat4>(), 0.01f, glm::vec3{-1.f, 1.f, 1.f}) * glm::vec4(meshes[1]->getPosition(), 1.f)
//            );
}

void prepareCamera() {
    camera = std::make_shared<PerspectiveCamera>(
            glm::vec3{0.f, 0.f, 15.f},
            glm::vec3{0.f, 1.f, 0.f},
            glm::vec3{1.f, 0.f, 0.f},
            60.f,
            static_cast<float>(app.getWidth()) / static_cast<float>(app.getHeight()),
            0.1f, 1000.f);
//    camera = std::make_shared<OrthographicCamera>(
//            glm::vec3{0.f, 0.f, 1.f},
//            glm::vec3{0.f, 1.f, 0.f},
//            glm::vec3{1.f, 0.f, 0.f},
//            -10.f, 10.f, 10.f, -10.f, 10.f, -10.f);
    cameraController = std::make_unique<TrackBallController>(camera, 0.2f, 0.2f, 0.005f);
//    cameraController = std::make_unique<GameCameraController>(camera, 0.2f, 0.2f, 0.1f);
}

void prepareMeshes() {
    meshes.emplace_back(std::make_shared<Mesh>(
            glm::vec3{0.f, 0.f, 0.f}, 20.f, 30.f, 0.f, glm::vec3{1.f, 1.f, 1.f},
            Geometry::createBox(4.f),
            std::make_shared<PhongMaterial>(
                    std::make_shared<Texture>("assets/textures/box.png", 0),
                    std::make_shared<Texture>("assets/textures/sp_mask.png", 1), 32.f)
    ));
    meshes.emplace_back(std::make_shared<Mesh>(
            glm::vec3{3.f, 3.f, 3.f}, 0.f, 0.f, 0.f, glm::vec3{1.f, 1.f, 1.f},
            Geometry::createSphere(0.2f),
            std::make_shared<WhiteMaterial>()
    ));
    meshes.emplace_back(std::make_shared<Mesh>(
            glm::vec3{6.f, 2.f, 4.f}, 0.f, 0.f, 8.f, glm::vec3{1.f, 1.f, 1.f},
            Geometry::createSphere(2.f),
            std::make_shared<PhongMaterial>(
                    std::make_shared<Texture>("assets/textures/earth.jpg", 0),
                    std::make_shared<Texture>("assets/textures/white.jpg", 1), 32.f)
    ));
}

void prepareLight() {
//    directionalLight = std::make_shared<DirectionalLight>(
//            glm::vec3{1.f, 1.f, 1.f}, 0.5f, glm::vec3{-1.0f, -0.3f, -0.7f}
//    );
    pointLight = std::make_shared<PointLight>(
            glm::vec3{1.f, 1.f, 1.f}, 1.f, glm::vec3{3.f, 3.f, 3.f}, 0.017f, 0.07f, 1.f
            );
    ambientLight = std::make_shared<AmbientLight>(
            glm::vec3{0.1f, 0.1f, 0.1f}
    );
}

void prepareShader() {
    renderer->addShader(MaterialType::PHONG_MATERIAL,
                        "./assets/shaders/phong_point_light.vert", "./assets/shaders/phong_point_light.frag");
    renderer->addShader(MaterialType::WHITE_MATERIAL,
                        "./assets/shaders/white.vert", "./assets/shaders/white.frag");
}

void prepare() {
    renderer = std::make_unique<Renderer>();
    prepareCamera();
    prepareMeshes();
    prepareLight();
    prepareShader();
}

int main() {

    if (!app.init(800, 600, "glStudy")) {
        return -1;
    }

    setCallback();

    // 设置视口大小 清理颜色
    GL_CALL(glViewport(0, 0, app.getWidth(), app.getHeight()));
    GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.f));

    prepare();
    while (app.update()) {
        doTransform();
        cameraController->update();
        // 渲染操作
        renderer->render(meshes, camera, pointLight, ambientLight);
    }
    { decltype(meshes) temp(std::move(meshes)); }
    app.destroy();

    return 0;
}

