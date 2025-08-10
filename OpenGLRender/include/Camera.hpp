#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera
{
public:
    // 构造函数
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = -90.0f, float pitch = 0.0f);

    // 获取视图矩阵
    glm::mat4 getViewMatrix() const;

    // 处理键盘输入（持续按键）
    void processKeyboard(int key, float deltaTime);

    // 处理鼠标移动
    void processMouseMovement(float xoffset, float yoffset,
                              bool constrainPitch = true);

    // 处理鼠标滚轮
    void processMouseScroll(float yoffset);

    // 获取投影矩阵
    glm::mat4 getProjectionMatrix(float aspect) const;

    // 属性访问
    glm::vec3 getPosition() const { return position; }
    glm::vec3 getFront() const { return front; }
    float getZoom() const { return zoom; }

private:
    void updateCameraVectors();

    // 相机属性
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    // 欧拉角
    float yaw;
    float pitch;

    // 相机参数
    float movementSpeed = 2.5f;
    float mouseSensitivity = 0.1f;
    float zoom = 45.0f;
};