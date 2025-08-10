// Window.cpp
#include "Window.hpp"
#include <iostream>

Window::Window(const Config &config)
    : width(config.width), height(config.height), title(config.title)
{

    // 初始化GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    // 配置GLFW窗口
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config.glMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config.glMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    // glfwWindowHint(GLFW_SAMPLES, config.samples);

    // 创建窗口
    handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!handle)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    // 设置当前上下文
    glfwMakeContextCurrent(handle);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    // 设置默认窗口回调
    glfwSetKeyCallback(handle, forwardKeyCallback);
    // glfwSetCursorPosCallback(handle, forwardCursorPosCallback);
    // glfwSetFramebufferSizeCallback(handle, forwardFramebufferSizeCallback);

    // 存储窗口指针以用于回调
    glfwSetWindowUserPointer(handle, this);
    // 初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(handle);
        handle = nullptr;
    }
    // 设置视口
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    // glDepthFunc(GL_LESS);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 渲染前设置（按渲染顺序调整）

    glDisable(GL_CULL_FACE);
}

Window::~Window()
{
    if (handle)
    {
        glfwDestroyWindow(handle);
    }
    glfwTerminate();
}

// 移动构造函数
Window::Window(Window &&other) noexcept
    : handle(other.handle), width(other.width),
      height(other.height), title(std::move(other.title)),
      keyCallback(std::move(other.keyCallback)),
      mouseCallback(std::move(other.mouseCallback)),
      resizeCallback(std::move(other.resizeCallback))
{

    other.handle = nullptr; // 防止资源被释放

    // 更新GLFW回调的用户指针
    if (handle)
    {
        glfwSetWindowUserPointer(handle, this);
    }
}

// 移动赋值运算符
Window &Window::operator=(Window &&other) noexcept
{
    if (this != &other)
    {
        // 释放现有资源
        if (handle)
        {
            glfwDestroyWindow(handle);
        }

        // 转移所有权
        handle = other.handle;
        width = other.width;
        height = other.height;
        title = std::move(other.title);
        keyCallback = std::move(other.keyCallback);
        mouseCallback = std::move(other.mouseCallback);
        resizeCallback = std::move(other.resizeCallback);

        other.handle = nullptr; // 防止资源被释放

        // 更新GLFW回调的用户指针
        if (handle)
        {
            glfwSetWindowUserPointer(handle, this);
        }
    }
    return *this;
}

bool Window::shouldClose() const
{
    return handle ? glfwWindowShouldClose(handle) : true;
}

void Window::swapBuffers()
{
    if (handle)
    {
        glfwSwapBuffers(handle);
    }
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::clear()
{
    if (handle)
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}

// 回调设置函数
void Window::setKeyCallback(KeyCallback callback)
{
    keyCallback = std::move(callback);
}

void Window::setMouseCallback(MouseCallback callback)
{
    mouseCallback = std::move(callback);
}

void Window::setResizeCallback(ResizeCallback callback)
{
    resizeCallback = std::move(callback);
}

// 静态GLFW回调转发函数
void Window::forwardKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (auto *win = static_cast<Window *>(glfwGetWindowUserPointer(window)))
    {
        if (win->keyCallback)
        {
            win->keyCallback(key, action);
        }
    }
}

void Window::forwardCursorPosCallback(GLFWwindow *window, double xpos, double ypos)
{
    if (auto *win = static_cast<Window *>(glfwGetWindowUserPointer(window)))
    {
        if (win->mouseCallback)
        {
            win->mouseCallback(xpos, ypos);
        }
    }
}

void Window::forwardFramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    if (auto *win = static_cast<Window *>(glfwGetWindowUserPointer(window)))
    {
        win->width = width;
        win->height = height;
        glViewport(0, 0, width, height);

        if (win->resizeCallback)
        {
            win->resizeCallback(width, height);
        }
    }
}

void Window::bindCamera(Camera *camera)
{
    this->camera = camera;
    setMouseCallback([this](double x, double y)
                     { 
            if(firstMouse) {
                lastX = x;
                lastY = y;
                firstMouse = false;
            }
            float xoffset = x - lastX;
            float yoffset = lastY - y; // 反转Y轴
            lastX = x;
            lastY = y;
            this->camera->processMouseMovement(xoffset, yoffset); });
}