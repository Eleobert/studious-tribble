#pragma once


#include <string>
#include <iostream>
#include <fstream>
#include <Transformation.h>

#include<experimental/optional>

#include <glm/glm.hpp>

/*
enum class ShaderType
{
    vertex   = gl::GL_VERTEX_SHADER,
    fragment = gl::GL_FRAGMENT_SHADER
};*/

class Shader
{
    unsigned int program;
    unsigned int vshader;
    unsigned int fshader;
    

    void compileShaders();
    void compileShader(unsigned int shaderType, unsigned int& id, const std::string& path);
    void linkShaders();

public:
    Shader(const std::string& vertexShaderSourcePath, const std::string& fragmentShaderSourcePath);
    void use();
    void setUniform4f(const char* name, float x, float y, float z, float w);
    void setUniformf(const char* name, float value);
    void setUniformMat4(const char* name, glm::mat4 value);
    /*void setTransformation(const Transformation& trans, 
            std::experimental::optional<const char*> translationUniformName,
            std::experimental::optional<const char*> rotationUniformName,
            std::experimental::optional<const char*> scaleUniformName);*/

};
