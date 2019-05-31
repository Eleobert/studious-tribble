#include <Camera.h>
#include <Mouse.h>

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <algorithm>

Camera::Camera(GLFWwindow* window, glm::vec3 position, glm::vec3 target):
    window(window), position(position), target(target)
{
    updateCoordinatesSystem();
    update();
}

void Camera::update()
{
    yaw   += mouse.delta.x * cameraMouseSensitivity;
    pitch += mouse.delta.y * cameraMouseSensitivity;
    pitch = std::clamp(pitch, -89.0f, 89.0f);

    updateCoordinatesSystem();
}

void Camera::updateCoordinatesSystem()
{
    front.x = glm::cos(glm::radians(pitch)) * glm::cos(glm::radians(yaw));
    front.y = glm::sin(glm::radians(pitch));
    front.z = glm::cos(glm::radians(pitch)) * glm::sin(glm::radians(yaw));

    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    up    = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::view()
{
    return glm::lookAt(position, position + front, up);
}