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
#include "glframework/light/directional_light.h"
#include "glframework/light/ambient_light.h"
#include "glframework/light/point_light.h"
#include "glframework/light/spot_light.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

std::vector<std::shared_ptr<Object>> objects{};
std::shared_ptr<Camera> camera{nullptr};
std::unique_ptr<CameraController> cameraController{nullptr};
std::vector<std::shared_ptr<Light>> lights;
std::unique_ptr<Renderer> renderer{};

glm::vec3 clearColor{};

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
//    meshes[0]->rotateZ(0.5f);
//    meshes[2]->rotateY(1.f);
//    meshes[2]->setPosition(
//            glm::rotate(glm::identity<glm::mat4>(), 0.01f, glm::vec3{-1.f, 1.f, 1.f}) *
//            glm::vec4(meshes[2]->getPosition(), 1.f)
//    );
//    spotLight->rotateX(1.f);
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
//            -20.f, 20.f, 20.f, -20.f, 20.f, -20.f);
    cameraController = std::make_unique<TrackBallController>(camera, 0.2f, 0.2f, 0.005f);
//    cameraController = std::make_unique<GameCameraController>(camera, 0.2f, 0.2f, 0.1f);
}

void prepareScenes() {
    auto box = std::make_shared<Mesh>(
            glm::vec3{0.f, 0.f, 0.f}, 20.f, 30.f, 0.f, glm::vec3{1.f, 1.f, 1.f},
            Geometry::createBox(4.f),
            std::make_shared<PhongMaterial>(
                    std::make_shared<Texture>("assets/textures/box.png", 0),
                    std::make_shared<Texture>("assets/textures/sp_mask.png", 1), 32.f)
    );
    auto sphere = std::make_shared<Mesh>(
            glm::vec3{3.f, 3.f, 3.f}, 0.f, 0.f, 0.f, glm::vec3{1.f, 1.f, 1.f},
            Geometry::createSphere(0.2f),
            std::make_shared<LightMaterial>(glm::vec3{1.f, 1.f, 1.f})
    );
    auto earth = std::make_shared<Mesh>(
            glm::vec3{6.f, 2.f, 4.f}, 0.f, 0.f, 8.f, glm::vec3{1.f, 1.f, 1.f},
            Geometry::createSphere(2.f),
            std::make_shared<PhongMaterial>(
                    std::make_shared<Texture>("assets/textures/earth.jpg", 0),
                    std::make_shared<Texture>("assets/textures/white.jpg", 1), 32.f)
    );
    box->addChild(earth);
    auto scene = std::make_shared<Scene>();
    scene->addChild(box);
    scene->addChild(sphere);
    objects.emplace_back(std::move(scene));
}

void prepareLight() {
    lights.emplace_back(std::make_shared<DirectionalLight>(
            glm::vec3{1.f, 1.f, 1.f}, 0.5f, glm::vec3{-1.0f, -0.3f, -0.7f}
    ));
    lights.emplace_back(std::make_shared<PointLight>(
            glm::vec3{1.f, 1.f, 1.f}, 0.5f, glm::vec3{3.f, 3.f, 3.f}, 0.017f, 0.07f, 1.f
    ));
    lights.emplace_back(std::make_shared<PointLight>(
            glm::vec3{0.f, 0.8f, 0.8f}, 1.f, glm::vec3{-3.f, -3.f, -3.f}, 0.017f, 0.07f, 1.f
    ));
    lights.emplace_back(std::make_shared<PointLight>(
            glm::vec3{1.f, 0.f, 0.f}, 1.f, glm::vec3{-3.f, 3.f, -3.f}, 0.017f, 0.07f, 1.f
    ));
    lights.emplace_back(std::make_shared<SpotLight>(
            glm::vec3{1.f, 1.f, 1.f}, 0.9f, glm::vec3{3.f, 3.f, 3.f},
            glm::vec3{-1.f, -1.f, -1.f}, 10.f, 20.f
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
    ImGui_ImplGlfw_InitForOpenGL(app.getWindow(), true);
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
    GL_CALL(glfwGetFramebufferSize(app.getWindow(), &display_w, &display_h));
    // 重置视口大小
    GL_CALL(glViewport(0, 0, display_w, display_h));
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int main() {

    if (!app.init(800, 600, "glStudy")) {
        return -1;
    }

    setCallback();

    // 设置视口大小 清理颜色
    GL_CALL(glViewport(0, 0, app.getWidth(), app.getHeight()));

    prepare();
//    initImGui();
    while (app.update()) {
        doTransform();
        cameraController->update();
        // 渲染操作
        renderer->setClearColor(clearColor);
        renderer->render(objects, camera, lights);
//        renderImGui();
    }
    { decltype(objects) temp(std::move(objects)); }
    app.destroy();

    return 0;
}

