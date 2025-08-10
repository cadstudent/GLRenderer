#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : position(position), worldUp(up), yaw(yaw), pitch(pitch)
{
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix(float aspect) const
{
    return glm::perspective(glm::radians(zoom), aspect, 0.1f, 100.0f);
}

void Camera::processKeyboard(int key, float deltaTime)
{
    float velocity = movementSpeed * deltaTime;

    switch (key)
    {
    case GLFW_KEY_W:
        position += front * velocity;
        break;
    case GLFW_KEY_S:
        position -= front * velocity;
        break;
    case GLFW_KEY_A:
        position -= right * velocity;
        break;
    case GLFW_KEY_D:
        position += right * velocity;
        break;
    case GLFW_KEY_Q:
        position -= worldUp * velocity;
        break; // 下降
    case GLFW_KEY_E:
        position += worldUp * velocity;
        break; // 上升
        }
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // 防止屏幕翻转
    if (constrainPitch)
    {
        pitch = glm::clamp(pitch, -89.0f, 89.0f);
    }

    updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset)
{
    zoom = glm::clamp(zoom - yoffset, 1.0f, 90.0f);
}

void Camera::updateCameraVectors()
{
    // 计算新前向量
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);

    // 重新计算右向量和上向量
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}