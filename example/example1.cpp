/**
  ******************************************************************************
  * @file           : example1.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-4-17
  ******************************************************************************
  */

#include <iostream>
#include <ctime>
#include <format>
#include <memory>

#include "../glframework/core.h"
#include "../glframework/shader.h"
#include "../glframework/texture.h"
#include "../wrapper/wrapper.h"
#include "../application/application.h"
#include "../application/camera/orthographic_camera.h"
#include "../application/camera/perspective_camera.h"
#include "../application/camera/track_ball_controller.h"
#include "../glframework/geometry.h"
#include "../glframework/object/object.h"
#include "../glframework/object/scene.h"
#include "../glframework/object/mesh.h"
#include "../glframework/object/group.h"
#include "../glframework/renderer/renderer.h"
#include "../glframework/material/phong_material.h"
#include "../glframework/material/light_material.h"
#include "../glframework/light/directional_light.h"
#include "../glframework/light/ambient_light.h"
#include "../glframework/light/point_light.h"
#include "../glframework/tools/tools.h"

std::vector<std::shared_ptr<Object>> objects{};
std::shared_ptr<Camera> camera{nullptr};
std::unique_ptr<CameraController> cameraController{nullptr};
std::vector<std::shared_ptr<Light>> lights;
std::vector<std::shared_ptr<PointLight>> pointLights;
std::unique_ptr<Renderer> renderer{};

void setCallback() {
    // 窗口大小调整的回调函数
    glApp.setResizeCallback([](int width, int height) -> void {
        GL_CALL(glViewport(0, 0, width, height));
    });

    glApp.setKeyCallback([](int key, int scancode, int action, int mods) -> void {
        if (cameraController != nullptr) {
            cameraController->onKey(key, action, mods);
        }
    });

    glApp.setMouseButtonCallback([](int button, int action, int mods) -> void {
        if (cameraController != nullptr) {
            double xpos, ypos;
            glApp.getCursorPosition(xpos, ypos);
            cameraController->onMouse(button, action, xpos, ypos);
        }
    });

    glApp.setCursorPosCallback([](double xpos, double ypos) -> void {
        if (cameraController != nullptr) {
            cameraController->onCurse(xpos, ypos);
        }
    });

    glApp.setScrollCallback([](double xoffset, double yoffset) -> void {
        if (cameraController != nullptr) {
            cameraController->onScroll(static_cast<float>(yoffset));
        }
    });
}

void doTransform() {
    std::vector<std::shared_ptr<Object>> sceneChildren = objects[0]->getChildren();
    auto group1 = sceneChildren[0];
    auto group2 = sceneChildren[1];
    group1->rotateX(0.1f);
    group1->rotateZ(0.05f);
    group2->rotateX(0.03f);
    group2->rotateY(0.15f);

    std::vector<std::shared_ptr<Object>> group1Children = group1->getChildren();
    for (int i = 1; i <= 6; ++i) {
        glm::vec3 position, angles, scale;
        Tools::decompose(group1Children[i]->getModelMatrix(), position, angles, scale);
        pointLights[i - 1]->setPosition(position);
    }
}

void prepareCamera() {
    camera = std::make_shared<PerspectiveCamera>(
            glm::vec3{0.f, 0.f, 15.f},
            glm::vec3{0.f, 1.f, 0.f},
            glm::vec3{1.f, 0.f, 0.f},
            60.f,
            static_cast<float>(glApp.getWidth()) / static_cast<float>(glApp.getHeight()),
            0.1f, 1000.f);
    cameraController = std::make_unique<TrackBallController>(camera, 0.2f, 0.2f, 0.005f);
}

void prepareScenes() {
    auto box = std::make_shared<Mesh>(
            glm::vec3{0.f, 0.f, 0.f}, 0.f, 0.f, 0.f, glm::vec3{1.f, 1.f, 1.f},
            Geometry::createBox(4.f),
            std::make_shared<PhongMaterial>(
                    std::make_shared<Texture>("assets/textures/box.png", 0),
                    std::make_shared<Texture>("assets/textures/sp_mask.png", 1), 32.f)
    );
    auto sphere1 = std::make_shared<Mesh>(
            glm::vec3{0.f, 0.f, 3.f}, 0.f, 0.f, 0.f, glm::vec3{1.f, 1.f, 1.f},
            Geometry::createSphere(0.2f),
            std::make_shared<LightMaterial>(glm::vec3{0.f, 0.f, 1.f})
    );
    auto sphere2 = std::make_shared<Mesh>(
            glm::vec3{0.f, 0.f, -3.f}, 0.f, 0.f, 0.f, glm::vec3{1.f, 1.f, 1.f},
            Geometry::createSphere(0.2f),
            std::make_shared<LightMaterial>(glm::vec3{0.f, 1.f, 0.f})
    );
    auto sphere3 = std::make_shared<Mesh>(
            glm::vec3{0.f, 3.f, 0.f}, 0.f, 0.f, 0.f, glm::vec3{1.f, 1.f, 1.f},
            Geometry::createSphere(0.2f),
            std::make_shared<LightMaterial>(glm::vec3{0.f, 1.f, 1.f})
    );
    auto sphere4 = std::make_shared<Mesh>(
            glm::vec3{0.f, -3.f, 0.f}, 0.f, 0.f, 0.f, glm::vec3{1.f, 1.f, 1.f},
            Geometry::createSphere(0.2f),
            std::make_shared<LightMaterial>(glm::vec3{1.f, 0.f, 0.f})
    );
    auto sphere5 = std::make_shared<Mesh>(
            glm::vec3{3.f, 0.f, 0.f}, 0.f, 0.f, 0.f, glm::vec3{1.f, 1.f, 1.f},
            Geometry::createSphere(0.2f),
            std::make_shared<LightMaterial>(glm::vec3{1.f, 0.f, 1.f})
    );
    auto sphere6 = std::make_shared<Mesh>(
            glm::vec3{-3.f, 0.f, 0.f}, 0.f, 0.f, 0.f, glm::vec3{1.f, 1.f, 1.f},
            Geometry::createSphere(0.2f),
            std::make_shared<LightMaterial>(glm::vec3{1.f, 1.f, 0.f})
    );
    auto group1 = std::make_shared<Group>();
    group1->addChild(box);
    group1->addChild(sphere1);
    group1->addChild(sphere2);
    group1->addChild(sphere3);
    group1->addChild(sphere4);
    group1->addChild(sphere5);
    group1->addChild(sphere6);
    auto earth = std::make_shared<Mesh>(
            glm::vec3{6.f, 2.f, 4.f}, 0.f, 0.f, 8.f, glm::vec3{1.f, 1.f, 1.f},
            Geometry::createSphere(2.f),
            std::make_shared<PhongMaterial>(
                    std::make_shared<Texture>("assets/textures/earth.jpg", 0),
                    std::make_shared<Texture>("assets/textures/white.jpg", 1), 32.f)
    );
    auto group2 = std::make_shared<Group>();
    group2->addChild(earth);
    auto scene = std::make_shared<Scene>();
    scene->addChild(group1);
    scene->addChild(group2);
    objects.emplace_back(std::move(scene));
}

void prepareLight() {
    lights.emplace_back(std::make_shared<DirectionalLight>(
            glm::vec3{1.f, 1.f, 1.f}, 0.5f, glm::vec3{-1.0f, -0.3f, -0.7f}
    ));
    std::shared_ptr<PointLight> pointLight1 = std::make_shared<PointLight>(
            glm::vec3{0.f, 0.f, 1.f}, 0.5f, glm::vec3{0.f, 0.f, 3.f}, 0.017f, 0.07f, 1.f
    );
    std::shared_ptr<PointLight> pointLight2 = std::make_shared<PointLight>(
            glm::vec3{0.f, 1.f, 0.f}, 0.5f, glm::vec3{0.f, 0.f, -3.f}, 0.017f, 0.07f, 1.f
    );
    std::shared_ptr<PointLight> pointLight3 = std::make_shared<PointLight>(
            glm::vec3{0.f, 1.f, 1.f}, 0.5f, glm::vec3{0.f, 3.f, 0.f}, 0.017f, 0.07f, 1.f
    );
    std::shared_ptr<PointLight> pointLight4 = std::make_shared<PointLight>(
            glm::vec3{1.f, 0.f, 0.f}, 0.5f, glm::vec3{0.f, -3.f, 0.f}, 0.017f, 0.07f, 1.f
    );
    std::shared_ptr<PointLight> pointLight5 = std::make_shared<PointLight>(
            glm::vec3{1.f, 0.f, 1.f}, 0.5f, glm::vec3{3.f, 0.f, 0.f}, 0.017f, 0.07f, 1.f
    );
    std::shared_ptr<PointLight> pointLight6 = std::make_shared<PointLight>(
            glm::vec3{1.f, 1.f, 0.f}, 0.5f, glm::vec3{-3.f, 0.f, 0.f}, 0.017f, 0.07f, 1.f
    );
    lights.push_back(pointLight1);
    pointLights.push_back(pointLight1);
    lights.push_back(pointLight2);
    pointLights.push_back(pointLight2);
    lights.push_back(pointLight3);
    pointLights.push_back(pointLight3);
    lights.push_back(pointLight4);
    pointLights.push_back(pointLight4);
    lights.push_back(pointLight5);
    pointLights.push_back(pointLight5);
    lights.push_back(pointLight6);
    pointLights.push_back(pointLight6);
    lights.emplace_back(std::make_shared<AmbientLight>(
            glm::vec3{0.1f, 0.1f, 0.1f}
    ));
}

void prepareShader() {
    renderer->addShader(MaterialType::PHONG_MATERIAL,
                        "./assets/shaders/phong_example1.vert", "./assets/shaders/phong_example1.frag");
    renderer->addShader(MaterialType::LIGHT_MATERIAL,
                        "./assets/shaders/white.vert", "./assets/shaders/white.frag");
}

void prepare() {
    renderer = std::make_unique<Renderer>();
    prepareCamera();
    prepareScenes();
    prepareLight();
    prepareShader();
}

int main() {

    if (!glApp.init(800, 600, "glStudy")) {
        return -1;
    }

    setCallback();

    // 设置视口大小 清理颜色
    GL_CALL(glViewport(0, 0, glApp.getWidth(), glApp.getHeight()));

    prepare();
//    initImGui();
    while (glApp.update()) {
        doTransform();
        cameraController->update();
        // 渲染操作
        renderer->setClearColor(glm::vec3{0.2f, 0.2f, 0.2f});
        renderer->render(objects, camera, lights);
//        renderImGui();
    }
    { decltype(objects) temp(std::move(objects)); }
    glApp.destroy();

    return 0;
}

