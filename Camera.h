#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera
{
    glm::vec3 target;
    float yaw = -90.0f, pitch = 0;
    GLFWwindow* window;

    void updateCoordinatesSystem();
public:
    glm::vec3 position;

    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;

    float cameraMouseSensitivity = 0.5;

    Camera(GLFWwindow* window, glm::vec3 position, glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f));

    void update();
    glm::mat4 view();
};