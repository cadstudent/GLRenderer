// Window.h
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <functional>
#include "Camera.hpp"

struct Config
{
    int width = 1024;
    int height = 768;
    std::string title = "OpenGL Renderer";
    int glMajor = 4;
    int glMinor = 6;
    int samples = 4;
};

class Window
{
public:
    // 窗口配置结构

    // 回调函数类型
    using KeyCallback = std::function<void(int key, int action)>;
    using MouseCallback = std::function<void(double x, double y)>;
    using ResizeCallback = std::function<void(int width, int height)>;

    Window(const Config &config);
    ~Window();

    // 删除拷贝构造和赋值
    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;

    // 移动语义支持
    Window(Window &&other) noexcept;
    Window &operator=(Window &&other) noexcept;

    // 窗口管理
    bool shouldClose() const;
    void swapBuffers();
    void pollEvents();
    void clear();

    // 回调设置
    void setKeyCallback(KeyCallback callback);
    void setMouseCallback(MouseCallback callback);
    void setResizeCallback(ResizeCallback callback);

    //add:camera
    void bindCamera(Camera *camera);

    // 获取信息
    int getWidth() const
    {
        return width;
    }
    int getHeight() const { return height; }
    float getAspectRatio() const { return static_cast<float>(width) / height; }
    GLFWwindow *getNativeHandle() const { return handle; }

private:
    GLFWwindow *handle = nullptr;
    int width;
    int height;
    std::string title;
    Camera *camera = nullptr;
    bool firstMouse = true;
    double lastX = 0.0;
    double lastY = 0.0;

    // 回调存储
    KeyCallback keyCallback;
    MouseCallback mouseCallback;
    ResizeCallback resizeCallback;

    // GLFW回调转发函数
    static void forwardKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void forwardCursorPosCallback(GLFWwindow *window, double xpos, double ypos);
    static void forwardFramebufferSizeCallback(GLFWwindow *window, int width, int height);
};