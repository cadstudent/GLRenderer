#include <glad/glad.h>
#include <iostream>
#include "Window.hpp"
#include "Shader.hpp"
#include "Model.hpp"
#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

int main()
{

    Config config;
    config.title = "OpenGL Raster Renderer";
    config.width = 1200;
    config.height = 800;
    config.glMajor = 3;
    config.glMinor = 3; // 要求OpenGL 3.3

    Window window(config);
    Camera camera;
    window.bindCamera(&camera);

    // 设置按键回调
    window.setKeyCallback([&window](int key, int action)
                          {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
                std::cout << "ESC pressed - exiting application" << std::endl;
                glfwSetWindowShouldClose(window.getNativeHandle(), GLFW_TRUE);
            } });

    // 设置鼠标回调
    window.setMouseCallback([](double x, double y)
                            {
                                // 用于后续的相机控制
                            });

    // 设置窗口大小变化回调
    window.setResizeCallback([](int width, int height)
                             { std::cout << "Window resized to: " << width << "x" << height << std::endl; });

    // 加载Shader
    Shader shader("../shader/model.vs", "../shader/model.fs");
    Shader testShader("../shader/test.vs", "../shader/test.fs");

    // 加载模型
    Model ourModel("../assets/mary/Marry.obj");
    // Model ourModel("../assets/Models/backpack/backpack.obj");
    //  Model ourModel("../assets/bunny/bunny.obj");
    // Model ourModel("../assets/Models/nanosuit/nanosuit.obj");
    ourModel.CoutInfo();

    // 设置光照属性
    // shader.use();
    // shader.setVec3("light.position", glm::vec3(1.0f, 1.0f, 2.0f));
    // shader.setVec3("light.ambient", glm::vec3(0.2f));
    // shader.setVec3("light.diffuse", glm::vec3(0.5f));
    // shader.setVec3("light.specular", glm::vec3(1.0f));
    // shader.setVec3("viewPos", glm::vec3(0.0f, 0.0f, 3.0f));
    // shader.setFloat("material.shininess", 32.0f);

    // 主循环
    float lastFrame = glfwGetTime();
    while (!window.shouldClose())
    {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        window.clear();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDepthFunc(GL_LESS);
        glEnable(GL_DEPTH_TEST);
        // glDepthMask(GL_TRUE);             // 确保深度写入开启
        // glEnable(GL_POLYGON_OFFSET_FILL); // 缺少多边形偏移
        // glPolygonOffset(0.1, 1.0);
        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // 视图/投影变换
        glm::mat4 projection = glm::perspective(glm::radians(55.0f),
                                                window.getAspectRatio(), 1.0f, 100.0f);
        glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 1.0f, 3.0f),
                                     glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        // 模型变换
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f));
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        shader.use();
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);
        shader.setMat4("model", model);
        ourModel.draw(shader.ID);

        // testShader.use();
        // testShader.setMat4("model", model);
        // testShader.setMat4("view", view);
        // testShader.setMat4("projection", projection);
        // ourModel.loadTriangle(testShader.ID);

        window.pollEvents();
        window.swapBuffers();
    }

    return 0;
}
