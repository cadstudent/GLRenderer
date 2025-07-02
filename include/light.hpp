// light.hpp
#pragma once

#include <glm/glm.hpp>

class Light {
public:
    enum LightType {
        DIRECTIONAL,
        POINT,
        SPOT
    };

    Light(LightType type, 
          glm::vec3 position, 
          glm::vec3 direction,
          glm::vec3 ambient,
          glm::vec3 diffuse,
          glm::vec3 specular,
          float constant = 1.0f,
          float linear = 0.09f,
          float quadratic = 0.032f,
          float cutOff = glm::cos(glm::radians(12.5f)),
          float outerCutOff = glm::cos(glm::radians(15.0f)));

    LightType type;
    glm::vec3 position;
    glm::vec3 direction;
    
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    // 点光源衰减参数
    float constant;
    float linear;
    float quadratic;

    // 聚光灯参数
    float cutOff;
    float outerCutOff;
};