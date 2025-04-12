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

std::unique_ptr<Shader> shader;
std::unique_ptr<Texture> texture;
glm::mat4 transform{1.f};
std::unique_ptr<CameraController> cameraController{nullptr};
std::shared_ptr<Camera> camera{nullptr};
std::unique_ptr<Geometry> geometry{nullptr};

// 平行光
glm::vec3 lightDirection(-1.0f, -0.3f, -0.7f);
glm::vec3 lightColor(1.f, 1.f, 1.f);
float specularIntensity = 0.5f;
// 环境光
glm::vec3 ambientColor(0.2f, 0.2f, 0.2f);


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
            cameraController->onScroll(yoffset);
        }
    });
}

void preTransform() {
    transform = glm::translate(transform, glm::vec3(0.0, 0.f, 0.f));
}

void doTransform() {
    float angle = 0.2f;
    transform = glm::rotate(transform, glm::radians(angle), glm::vec3{0.f, 0.f, 1.f});
    transform = glm::rotate(transform, glm::radians(angle / 3), glm::vec3{0.f, 1.f, 0.f});
}

void prepareVAO() {
//    geometry = Geometry::createPlane(2.f, 3.f);
//    geometry = Geometry::createBox(2.f);
    geometry = Geometry::createSphere(2.f, 50, 50);
}

void prepareShader() {
    shader = std::make_unique<Shader>("./assets/shaders/vertex.glsl", "./assets/shaders/fragment.glsl");
}

void prepareTexture() {
//    texture = std::make_unique<Texture>("assets/textures/back.png", 0);
//    texture = std::make_unique<Texture>("assets/textures/goku.jpg", 0);
//    glassTexture = new Texture("assets/textures/glass.jpg", 0);
//    landTexture = new Texture("assets/textures/land.jpg", 1);
//    noiseTexture = new Texture("assets/textures/noise.jpg", 2);
//    texture = std::make_unique<Texture>("assets/textures/ge.jpg", 0);
    texture = std::make_unique<Texture>("assets/textures/earth.jpg", 0);
}

void prepareCamera() {
    camera = std::make_shared<PerspectiveCamera>(
            glm::vec3{0.f, 0.f, 5.f},
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

void prepareState() {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearDepth(1.f);
}

void render() {
    // 画布清理
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    // 绑定vao
    GL_CALL(glBindVertexArray(geometry->getVao()));
    // 绑定program
    shader->begin();
    shader->setInt("sampler", 0);
    shader->setMatrix4x4("modelMatrix", transform);
    shader->setMatrix3x3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(transform))));
    shader->setMatrix4x4("viewMatrix", camera->getViewMatrix());
    shader->setMatrix4x4("projectionMatrix", camera->getProjectionMatrix());
    shader->setVector3f("cameraPosition", camera->getPosition());

    // light
    shader->setVector3f("lightDirection", lightDirection);
    shader->setVector3f("lightColor", lightColor);
    shader->setFloat("specularIntensity", specularIntensity);
    shader->setVector3f("ambientColor", ambientColor);

    texture->bind();
    // 绑定ebo
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->getEbo()));
    // 绘制
    GL_CALL(glDrawElements(GL_TRIANGLES, geometry->getIndicesCount(), GL_UNSIGNED_INT, reinterpret_cast<void *>(0)));

    shader->end();
    // 解绑vao ebo
    GL_CALL(glBindVertexArray(0));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

int main() {

    if (!app.init(800, 600, "glStudy")) {
        return -1;
    }

    setCallback();

    // 设置视口大小 清理颜色
    GL_CALL(glViewport(0, 0, app.getWidth(), app.getHeight()));
    GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.f));

    prepareState();
    prepareVAO();
    prepareShader();
    prepareTexture();
    preTransform();
    prepareCamera();
    while (app.update()) {
        doTransform();
        cameraController->update();
        // 渲染操作
        render();
    }
    texture.reset();
    shader.reset();
    geometry.reset();
    app.destroy();

    return 0;
}

