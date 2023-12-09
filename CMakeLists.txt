cmake_minimum_required(VERSION 3.26)
project(SeNes2D)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(dependencies/glfw-3.3.7)
add_subdirectory(Utils)
add_subdirectory(Wrappers)
add_subdirectory(Objects/WorldObject3D)
add_subdirectory(Objects/Camera)
add_subdirectory(Objects/Shapes)

add_executable(SeNes2D
        main.cpp
        dependencies/GLAD/glad.c
)

target_link_libraries(SeNes2D PUBLIC glfw Wrappers)

target_include_directories(SeNes2D PUBLIC
        dependencies/GLEW/include
        dependencies/GLAD
        dependencies/KHR
        dependencies/GLM
        Wrappers/include/*
)

include(cmake/Deploy.cmake)
MyDeploy(SeNes2D)