#include <Mouse.h>
#include <iostream>

Mouse data;

const Mouse& mouse = data;
glm::vec2 oldPos;

void initMouse(GLFWwindow *window)
{
    data.pos    = glm::vec2(0.0f, 0.0f);    
    data.delta  = glm::vec2(0.0f, 0.0f);
    oldPos      = glm::vec2(0.0f, 0.0f);
    data.scrool = Scrool{0.0f, 0.0f};

    glfwSetCursorPosCallback(window, 
    [](GLFWwindow* window, double x, double y)
    {
        data.pos.x = x;
        data.pos.y = y;
        //call the function only in the first call to this callback
        static int once = []{
            oldPos = data.pos;
            return 0;
        }();
    });
}


void mouseCalculateDelta()
{
    data.delta.x = data.pos.x - oldPos.x;
    data.delta.y = oldPos.y - data.pos.y;
    oldPos = data.pos;
}
