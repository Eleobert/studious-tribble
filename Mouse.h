#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

struct Scrool
{
    float up, down;
};

struct Mouse
{
    glm::vec2 pos;
    glm::vec2 delta;
    Scrool scrool;
};

extern const Mouse& mouse;

void initMouse(GLFWwindow* window);
void mouseCalculateDelta();
