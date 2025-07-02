#pragma once
#include <string>
#include <iostream>
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.hpp"
#include "model.hpp"
#include "camera.hpp"

using namespace std;

class Application
{
private:
    GLFWwindow* window;
    int width, height;
    std::string title;
    
    // 相机参数
    //glm::vec3 cameraPosition;
    //glm::vec3 cameraFront;
    //glm::vec3 cameraUp;
    float fov;
    Camera camera;
    bool firstMouse;
    float lastX;
    float lastY;
    
    // 时间管理
    float deltaTime;
    float lastFrame;

    std::string vsPath;
    std::string fsPath;
    std::vector<std::string> models;
  

public:
    Application() 
        : window(nullptr), width(0), height(0),
          camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
          firstMouse(true), lastX(0.0f), lastY(0.0f),
          fov(45.0f), deltaTime(0.0f), lastFrame(0.0f)
         {
            lastX = width / 2.0f;
            lastY = height / 2.0f;
         }

    ~Application() {
        if (window) {
            // 清除用户指针关联
            glfwSetWindowUserPointer(window, nullptr);
            glfwDestroyWindow(window);
        }
        glfwTerminate();
    }
  
    // 静态回调函数声明
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    
    // 处理键盘输入
 void processInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
     if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
        static bool captureMouse = true;
        captureMouse = !captureMouse;
        if (captureMouse)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        else
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        // 避免连续切换，等待释放
        glfwWaitEventsTimeout(0.5);
    }
    
    // 使用Camera类的方法处理移动
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

    void loadvsFile(std::string path){
        vsPath = path;
        cout<<"vsPath:"<<vsPath<<"load success!"<<endl;
    }
    void loadfsFile(std::string path){
        fsPath = path;
        cout<<"fsPath:"<<fsPath<<"load success!"<<endl;
    }
    void loadmodel(std::string path){
        models.push_back(path);
        cout<<"model["<<models.size()<<"]:"<<path<<"load success!"<<endl;
    }
    // 初始化应用程序
    bool Init(int width = 1280, int height = 720, const std::string& title = "OpenGL Renderer") {
        this->width = width;
        this->height = height;
        this->title = title;
        
        // 初始化GLFW
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return false;
        }
        
        // 配置GLFW
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      
        
        // 创建窗口
        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }
        
        // 设置上下文
        glfwMakeContextCurrent(window);
        glfwSwapInterval(0); // 关闭垂直同步
        
        // 设置窗口用户指针
        glfwSetWindowUserPointer(window, this);
        
         // 设置回调事件
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);
    
        // 捕获鼠标（可选）
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        
        // 初始化GLAD
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            glfwDestroyWindow(window);
            window = nullptr;
            return false;
        }
    
        // 启用深度测试
        glEnable(GL_DEPTH_TEST);
        
        // 设置初始时间
        lastFrame = static_cast<float>(glfwGetTime());
        
        return true;
    }
    
    // 运行主循环
    void Run() {
        Shader ourShader(vsPath.c_str(),fsPath.c_str());
        vector<Model> ourModels;
        for(auto& mod:models){
            Model model(mod.c_str());
            ourModels.push_back(model);
        }
        while (!glfwWindowShouldClose(window)) {
            // 计算帧时间
            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            
            // 处理输入
            processInput();
            glfwPollEvents();
            
            // 渲染
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glm::mat4 projection = glm::perspective(
            glm::radians(camera.Zoom), 
            (float)width / (float)height, 
            0.1f, 100.0f
            );
            glm::mat4 view = camera.GetViewMatrix();
            
            ourShader.use();
            ourShader.setMat4("projection", projection);
            ourShader.setMat4("view", view);
            for(auto& mod:ourModels){
                // 设置模型矩阵
                glm::mat4 modelMatrix = glm::mat4(1.0f);
                // 可以在这里调整模型的位置/旋转/缩放
                // modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -1.0f, 0.0f));
                // modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
                ourShader.setMat4("model", modelMatrix);
            
                mod.Draw(ourShader);
            }
            // 交换缓冲区
            glfwSwapBuffers(window);
        }
    }

};

// 静态回调函数实现
void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // 获取Application实例
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app) {
        app->width = width;
        app->height = height;
        glViewport(0, 0, width, height);
    }
}

void Application::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    // 获取Application实例
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (!app) return;
    
    float xposf = static_cast<float>(xpos);
    float yposf = static_cast<float>(ypos);
    
    if (app->firstMouse) {
        app->lastX = xposf;
        app->lastY = yposf;
        app->firstMouse = false;
    }
    
    float xoffset = xposf - app->lastX;
    float yoffset = app->lastY - yposf; // 反转Y轴
    
    app->lastX = xposf;
    app->lastY = yposf;
    
    // 应用灵敏度
    float sensitivity = 0.01f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    
    app->camera.ProcessMouseMovement(xoffset, yoffset);
 
    // 暂时输出调试信息
    std::cout << "Mouse moved: (" << xoffset << ", " << yoffset << ")" << std::endl;
}
//
// 鼠标滚轮回调
void Application::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (!app) return;
    
    app->camera.ProcessMouseScroll(static_cast<float>(yoffset));
    // 输出调试信息
    std::cout << "FOV changed to: " << app->fov << std::endl;
}  
