/**
  ******************************************************************************
  * @file           : application.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-3-14
  ******************************************************************************
  */

#include "application.h"

// glad头文件的引用需要在glfw之前
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Application &Application::getInstance() {
    static Application application;
    return application;
}

bool Application::init(const uint32_t &width, const uint32_t &height, const char *title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // 主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // 次版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 核心模式

    this->mWidth = width;
    this->mHeight = height;

    // 创建窗体对象
    this->mWindow = glfwCreateWindow(
            static_cast<int>(this->mWidth),
            static_cast<int>(this->mHeight),
            title, nullptr, nullptr
    );
    if (this->mWindow == nullptr) {
        return false;
    }
    // 设置当前窗体为opengl绘制的舞台
    glfwMakeContextCurrent(this->mWindow);

    // 使用glad加载所有当前版本的opengl函数
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        return false;
    }

    glfwSetWindowUserPointer(this->mWindow, this);

    glfwSetFramebufferSizeCallback(
            this->mWindow,
            [](GLFWwindow *window, int width, int height) -> void {
                auto *self = reinterpret_cast<Application *>(glfwGetWindowUserPointer(window));
                if (self->mResizeCallback != nullptr) {
                    self->mResizeCallback(width, height);
                }
            });
    // 键盘响应
    glfwSetKeyCallback(
            this->mWindow,
            [](GLFWwindow *window, int key, int scancode, int action, int mods) -> void {
                auto *self = reinterpret_cast<Application *>(glfwGetWindowUserPointer(window));
                if (self->mKeyCallback != nullptr) {
                    self->mKeyCallback(key, scancode, action, mods);
                }
            });
    // 鼠标点击事件响应
    glfwSetMouseButtonCallback(
            this->mWindow,
            [](GLFWwindow *window, int button, int action, int mods) -> void {
                auto *self = reinterpret_cast<Application *>(glfwGetWindowUserPointer(window));
                if (self->mMouseButtonCallback != nullptr) {
                    self->mMouseButtonCallback(button, action, mods);
                }
            });
    // 鼠标移动事件响应
    glfwSetCursorPosCallback(
            this->mWindow,
            [](GLFWwindow *window, double xpos, double ypos) -> void {
                auto *self = reinterpret_cast<Application *>(glfwGetWindowUserPointer(window));
                if (self->mCursorPosCallback != nullptr) {
                    self->mCursorPosCallback(xpos, ypos);
                }
            });

    glfwSetScrollCallback(
            this->mWindow,
            [] (GLFWwindow* window, double xoffset, double yoffset) {
                auto *self = reinterpret_cast<Application *>(glfwGetWindowUserPointer(window));
                if (self->mScrollCallback != nullptr) {
                    self->mScrollCallback(xoffset, yoffset);
                }
            });

    return true;
}

bool Application::update() {
    glfwPollEvents(); // 接收并分发窗口消息
    glfwSwapBuffers(this->mWindow); // 切换双缓存
    return !glfwWindowShouldClose(this->mWindow);
}

void Application::destroy() {
    glfwTerminate();
}

void Application::getCursorPosition(double &xpos, double &ypos) const {
    glfwGetCursorPos(this->mWindow, &xpos, &ypos);
}
