#include<Shader.h>


#include <slam/slam.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Cube.h>
#include <Camera.h>
#include <Mouse.h>
#include <iomanip>

constexpr int width = 800;
constexpr int height = 600;


void processInput(GLFWwindow* window, Camera& camera);

std::ostream& operator<<(std::ostream& stream, glm::vec3 vec)
{
    std::cout << vec.x << ' ' << vec.y << ' ' << vec.z;
    return stream;
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Studious Tribble", nullptr, nullptr);

    if(window == nullptr)
    {
        std::cerr << "Hoo my god! Failed to create the window.\n";
        return -1;
    }

    glfwMakeContextCurrent(window);

    try
    {
        gl::init();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    gl::glEnable(gl::GL_DEBUG_OUTPUT);
    gl::glEnable(gl::GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    gl::glDebugMessageCallback([]
        (gl::GLenum source, gl::GLenum type, gl::GLuint id, gl::GLenum severity, gl::GLsizei length,
                  const gl::GLchar *message, const void *userParam)
        {
            std::cout << message << '\n';
        }, nullptr);



    Shader shader("../res/shaders/Vertex.vs", "../res/shaders/Fragment.fs");
    shader.use();

    Transformation trans;
    Cube cube;

    Camera camera(window, glm::vec3(0.0f, 0.0f, 3.0f));

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width/(float)height,
                            0.1f, 100.0f);
    shader.setUniformMat4("projection", proj);
    initMouse(window);

    mouseCalculateDelta();


    while(glfwWindowShouldClose(window) == false)
    {
        gl::glClearColor(1, 1, 1, 1);
        gl::glClear(gl::GL_COLOR_BUFFER_BIT | gl::GL_DEPTH_BUFFER_BIT);

        mouseCalculateDelta();
        
        processInput(window, camera);
        auto time = glfwGetTime();
        camera.update();

        shader.setUniformMat4("model", glm::mat4(1.0f));
        shader.setUniformMat4("view", camera.view());

        shader.use();

        cube.draw();
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
}


void processInput(GLFWwindow* window, Camera& camera)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 0.05f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.position += cameraSpeed * camera.front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.position -= cameraSpeed * camera.front;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.position -= cameraSpeed * camera.right;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.position += cameraSpeed * camera.right;
}
