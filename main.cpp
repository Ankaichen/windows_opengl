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
#include "glframework/object/scene.h"
#include "glframework/object/mesh.h"
#include "glframework/object/group.h"
#include "glframework/renderer/renderer.h"
#include "glframework/material/phong_material.h"
#include "glframework/material/light_material.h"
#include "glframework/material/depth_material.h"
#include "glframework/light/directional_light.h"
#include "glframework/light/ambient_light.h"
#include "glframework/light/point_light.h"
#include "glframework/light/spot_light.h"
#include "utils/assimp_loader.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

std::vector<std::shared_ptr<Object>> objects{};
std::shared_ptr<Camera> camera{nullptr};
std::unique_ptr<CameraController> cameraController{nullptr};
std::vector<std::shared_ptr<Light>> lights;
std::unique_ptr<Renderer> renderer{};

glm::vec3 clearColor{0.2f, 0.2f, 0.2f};

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
}

void prepareCamera() {
    camera = std::make_shared<PerspectiveCamera>(
            glm::vec3{0.f, 0.f, 15.f},
            glm::vec3{0.f, 1.f, 0.f},
            glm::vec3{1.f, 0.f, 0.f},
            60.f,
            static_cast<float>(glApp.getWidth()) / static_cast<float>(glApp.getHeight()),
            0.1f, 2000.f);
//    camera = std::make_shared<OrthographicCamera>(
//            glm::vec3{0.f, 0.f, 1.f},
//            glm::vec3{0.f, 1.f, 0.f},
//            glm::vec3{1.f, 0.f, 0.f},
//            -20.f, 20.f, 20.f, -20.f, 20.f, -20.f);
    cameraController = std::make_unique<TrackBallController>(camera, 0.2f, 0.2f, 0.005f);
//    cameraController = std::make_unique<GameCameraController>(camera, 0.2f, 0.2f, 0.1f);
}

void prepareScenes() {
//    std::shared_ptr<Object> obj = AssimpLoader::load("assets/fbx/Dragon 2.5_fbx.fbx");
//    std::shared_ptr<Object> obj = AssimpLoader::load("assets/fbx/bag/backpack.obj");
    objects.push_back(std::make_shared<Mesh>(
            Geometry::createPlane(900.f, 600.f),
            std::make_shared<PhongMaterial>(
                    Texture::createTexture("assets/textures/box.png", 0),
                    Texture::createTexture("assets/textures/sp_mask.png", 1),
                    32.f)
    ));
    auto pnong = std::make_shared<PhongMaterial>(
            Texture::createTexture("assets/textures/default.jpg", 0),
            Texture::createTexture("assets/textures/white.jpg", 1),
            32.f);
    pnong->setDepthWrite(true);
    pnong->setPolygonOffset(true);
    pnong->setPolygonOffsetType(GL_POLYGON_OFFSET_FILL);
    pnong->setPolygonOffsetParameters(1.f, 1.f);
    objects.push_back(std::make_shared<Mesh>(
            Geometry::createPlane(900.f, 600.f),
            std::move(pnong)
    ));
//    objects.push_back(std::make_shared<Mesh>(
//            Geometry::createPlane(5.f, 5.f),
//            std::make_shared<PhongMaterial>(
//                    Texture::createTexture("assets/textures/earth.jpg", 0),
//                    Texture::createTexture("assets/textures/white.jpg", 1),
//                    32.f)
//    ));

    objects[1]->setPosition(glm::vec3{2.f, 0.5f, -0.5f});
//    objects[2]->setPosition(glm::vec3{4.f, 1.f, -2.f});

objects[0]->rotateX(-88.f);
objects[1]->rotateX(-88.f);
}

//void prepareScenes() {
////    std::shared_ptr<Object> obj = AssimpLoader::load("assets/fbx/Dragon 2.5_fbx.fbx");
////    std::shared_ptr<Object> obj = AssimpLoader::load("assets/fbx/bag/backpack.obj");
//    objects.push_back(std::make_shared<Mesh>(
//            Geometry::createPlane(5.f, 5.f),
//            std::make_shared<DepthMaterial>()
//    ));
//    objects.push_back(std::make_shared<Mesh>(
//            Geometry::createPlane(5.f, 5.f),
//            std::make_shared<DepthMaterial>()
//    ));
//    objects.push_back(std::make_shared<Mesh>(
//            Geometry::createPlane(5.f, 5.f),
//            std::make_shared<DepthMaterial>()
//    ));
//
//    objects[1]->setPosition(glm::vec3{2.f, 0.5f, -1.f});
//    objects[2]->setPosition(glm::vec3{4.f, 1.f, -2.f});
//}

void prepareLight() {
    lights.emplace_back(std::make_shared<DirectionalLight>(
            glm::vec3{1.f, 1.f, 1.f}, 0.5f, glm::vec3{-1.0f, -0.3f, -0.7f}
    ));
    lights.emplace_back(std::make_shared<AmbientLight>(
            glm::vec3{0.1f, 0.1f, 0.1f}
    ));
}

void prepareShader() {
    renderer->addShader(MaterialType::PHONG_MATERIAL,
                        "./assets/shaders/phong.vert", "./assets/shaders/phong.frag");
    renderer->addShader(MaterialType::LIGHT_MATERIAL,
                        "./assets/shaders/white.vert", "./assets/shaders/white.frag");
    renderer->addShader(MaterialType::DEPTH_MATERIAL,
                        "./assets/shaders/depth.vert", "./assets/shaders/depth.frag");
}

void prepare() {
    renderer = std::make_unique<Renderer>();
    prepareCamera();
    prepareScenes();
    prepareLight();
    prepareShader();
}

void initImGui() {
    ImGui::CreateContext();// 创建ImGui上下文
    ImGui::StyleColorsDark();// 设置主题
    // 设置ImGui与GLFW和OpenGL的绑定
    ImGui_ImplGlfw_InitForOpenGL(glApp.getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

void renderImGui() {
    // 开启当前imgui渲染
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    // 决定当前gui上面有那些控件 从上到下
    ImGui::Begin("Hello World!");
    ImGui::Text("ChangeColor Demo");
    ImGui::Button("Test Button", ImVec2{40, 20});
    ImGui::ColorEdit3("Clear Color", reinterpret_cast<float *>(&clearColor));
    ImGui::End();
    // 执行UI渲染
    ImGui::Render();
    int display_w, display_h;
    GL_CALL(glfwGetFramebufferSize(glApp.getWindow(), &display_w, &display_h));
    // 重置视口大小
    GL_CALL(glViewport(0, 0, display_w, display_h));
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int main() {

    if (!glApp.init(1600, 1200, "glStudy")) {
        return -1;
    }

    setCallback();

    // 设置视口大小 清理颜色
    GL_CALL(glViewport(0, 0, glApp.getWidth(), glApp.getHeight()));

    prepare();
    initImGui();
    while (glApp.update()) {
        doTransform();
        cameraController->update();
        // 渲染操作
        renderer->setClearColor(clearColor);
        renderer->render(objects, camera, lights);
        renderImGui();
    }
    { decltype(objects) temp(std::move(objects)); }
    glApp.destroy();

    return 0;
}

