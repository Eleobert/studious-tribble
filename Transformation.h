#pragma once 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


struct Transformation
{
    glm::mat4 translation;
    glm::mat4 rotation;
    glm::mat4 scale;
    Transformation(): translation(1), rotation(1), scale(1)
    {}
};