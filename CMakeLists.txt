cmake_minimum_required(VERSION 3.26)
project(SeNes2D)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(dependencies/glfw-3.3.7)

add_executable(SeNes2D
        main.cpp
        dependencies/GLAD/glad.c

        Wrappers/source/Gl.cpp
        Wrappers/include/Gl.h
        Wrappers/include/Shader.h
        Wrappers/source/Shader.cpp
        Wrappers/include/ShaderProgram.h
        Wrappers/source/ShaderProgram.cpp
        Wrappers/source/Window.cpp
        Wrappers/include/Window.h
        Wrappers/include/Texture.h
        Wrappers/source/Texture.cpp
        Wrappers/include/VAO.h
        Wrappers/source/VAO.cpp
        Wrappers/include/VBO.h
        Wrappers/source/VBO.cpp

        Utils/source/Utils.cpp
        Utils/include/Utils.h
)

target_link_libraries(SeNes2D PUBLIC glfw)

target_include_directories(SeNes2D PUBLIC dependencies/GLEW/include)
target_include_directories(SeNes2D PUBLIC dependencies/GLAD)
target_include_directories(SeNes2D PUBLIC dependencies/KHR)
target_include_directories(SeNes2D PUBLIC dependencies/GLM)
target_include_directories(SeNes2D PUBLIC Wrappers/include/*)

include(cmake/Deploy.cmake)
MyDeploy(SeNes2D)