cmake_minimum_required(VERSION 3.0)

project(studious-tribble)
set(CMAKE_CXX_STANDARD 17)

add_executable(studious-tribble
    main.cpp
    Shader.h
    Shader.cpp
    Logger.h
    Logger.cpp
    Texture.h
    Texture.cpp
    Transformation.h
    Cube.h
    Cube.cpp
    Camera.h
    Camera.cpp
    Mouse.h
    Mouse.cpp
    #slam
    slam/slam.h
    slam/slam.cpp
    #stb
    stb/stb_image.h
    stb/stb_image.cpp
)

#add_custom_command(
#        TARGET studious-tribble PRE_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${PROJECT_SOURCE_DIR}/res
#        ${PROJECT_BINARY_DIR}/res
#        )

target_include_directories(studious-tribble PRIVATE  ${PROJECT_SOURCE_DIR})
target_link_libraries(studious-tribble GL glfw dl assimp)