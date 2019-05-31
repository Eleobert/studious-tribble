#pragma once

#include <vector>

class Cube
{
    std::vector<float> vertices;
    std::vector<float> colors;

    unsigned int vbo = 0;
    unsigned int vao = 0;

    void initData();
public:
    //Cube(gsl::span<float> vertices, std::experimental::optional<gsl::span<float*> > = std::experimental::nullopt);
    Cube();
    void draw();
};