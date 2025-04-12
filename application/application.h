/**
  ******************************************************************************
  * @file           : application.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-3-14
  ******************************************************************************
  */

#ifndef OPENGL_APPLICATION_H
#define OPENGL_APPLICATION_H

#include <cstdint>
#include <functional>
#include <string_view>

#define app (Application::getInstance())

class GLFWwindow;

using ResizeCallback = std::function<void(int, int)>;
using KeyCallBack = std::function<void(int, int, int, int)>;
using MouseButtonCallback = std::function<void(int, int, int)>;
using CursorPosCallback = std::function<void(double, double)>;
using ScrollCallback = std::function<void(double, double)>;

class Application {
public:
    ~Application() noexcept = default;

    static Application &getInstance();

    [[nodiscard]] uint32_t getWidth() const { return this->mWidth; }

    [[nodiscard]] uint32_t getHeight() const { return this->mHeight; }

    void getCursorPosition(double &xPos, double &yPos) const;

    bool init(const uint32_t &width, const uint32_t &xPos, std::string_view yPos);

    bool update();

    static void destroy();

    inline void setResizeCallback(const ResizeCallback &resizeCallback) { this->mResizeCallback = resizeCallback; }

    inline void setKeyCallback(const KeyCallBack &keyCallBack) { this->mKeyCallback = keyCallBack; }

    inline void setMouseButtonCallback(const MouseButtonCallback &mouseButtonCallback) {
        this->mMouseButtonCallback = mouseButtonCallback;
    }

    inline void setCursorPosCallback(const CursorPosCallback &cursorPosCallback) {
        this->mCursorPosCallback = cursorPosCallback;
    }

    inline void setScrollCallback(const ScrollCallback &scrollCallback) {
        this->mScrollCallback = scrollCallback;
    }

private:
    Application() = default;

private:
    uint32_t mWidth{0};
    uint32_t mHeight{0};
    GLFWwindow *mWindow{nullptr};

    ResizeCallback mResizeCallback{nullptr};
    KeyCallBack mKeyCallback{nullptr};
    MouseButtonCallback mMouseButtonCallback{nullptr};
    CursorPosCallback mCursorPosCallback{nullptr};
    ScrollCallback mScrollCallback{nullptr};
};


#endif //OPENGL_APPLICATION_H
