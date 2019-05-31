#include<Shader.h>
#include <slam/slam.h>
#include <TribLog.h>

#include <glm/gtc/type_ptr.hpp>


Shader::Shader(const std::string& vertexShaderSourcePath, const std::string& fragmentShaderSourcePath)
{
    compileShader(gl::GL_VERTEX_SHADER, vshader,  vertexShaderSourcePath);
    compileShader(gl::GL_FRAGMENT_SHADER, fshader, fragmentShaderSourcePath);
    linkShaders();
}

void Shader::compileShader(gl::GLenum shaderType, unsigned int& id, const std::string& path)
{
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    file.open(path);
    std::string source( (std::istreambuf_iterator<char>(file)) , std::istreambuf_iterator<char>());

    id = gl::glCreateShader(shaderType);
    const char *c_str = source.c_str();
    gl::glShaderSource(id, 1, &c_str, nullptr);
    gl::glCompileShader(id);

    int success = gl::GL_FALSE;
    gl::glGetShaderiv(id, gl::GL_COMPILE_STATUS, &success);

    if(success != gl::GL_TRUE)
    {
        char errorString[512];
        gl::glGetShaderInfoLog(id, sizeof(errorString), nullptr, errorString);
        log().error("Shader not compiled. ", path, '\n', errorString);
    }
}

void Shader::linkShaders()
{
    program = gl::glCreateProgram();
    gl::glAttachShader(program, vshader);
    gl::glAttachShader(program, fshader);
    gl::glLinkProgram(program);

    int success = gl::GL_FALSE;
    gl::glGetProgramiv(program, gl::GL_LINK_STATUS, &success);
    if(success != gl::GL_TRUE)
    {
        char errorString[512];
        gl::glGetShaderInfoLog(program, sizeof(errorString), nullptr, errorString);
        log().error("Shader program not linked.\n", errorString);
    }
}

void Shader::use()
{
    gl::glUseProgram(program);
}

void Shader::setUniform4f(const char* name, float x, float y, float z, float w)
{
    this->use();
    int location = gl::glGetUniformLocation(program, name);
    gl::glUniform4f(location, x, y, z, w);
}

void Shader::setUniformf(const char* name, float value)
{
    this->use();
    int location = gl::glGetUniformLocation(program, name);
    gl::glUniform1f(location, value);
}

void Shader::setUniformMat4(const char* name, glm::mat4 value)
{
    this->use();
    int location = gl::glGetUniformLocation(program, name);
    gl::glUniformMatrix4fv(location, 1, gl::GL_FALSE, glm::value_ptr(value));
}

/*void Shader::setTransformation(const Transformation& transf, 
            std::experimental::optional<const char*> translationUniformName,
            std::experimental::optional<const char*> rotationUniformName,
            std::experimental::optional<const char*> scaleUniformName)
{
    this->use();
    int location = 0;
    //const char* p;

    const char* transName = (translationUniformName ? *translationUniformName: "translation");
    const char* rotName   = (rotationUniformName ? *rotationUniformName: "rotation");
    const char* scaleName = (scaleUniformName ? *scaleUniformName: "scale");


    location = gl::glGetUniformLocation(program, transName);
    gl::glUniformMatrix4fv(location, 1, gl::GL_FALSE, glm::value_ptr(transf.translation));
    location = gl::glGetUniformLocation(program, rotName);
    gl::glUniformMatrix4fv(location, 1, gl::GL_FALSE, glm::value_ptr(transf.rotation));
    location = gl::glGetUniformLocation(program, scaleName);
    gl::glUniformMatrix4fv(location, 1, gl::GL_FALSE, glm::value_ptr(transf.scale));
}*/
