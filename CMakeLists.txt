cmake_minimum_required(VERSION 3.26)
project(SeNes2D)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(DEPENDENCIES_DIR_NAME dependencies)
set(DEPENDENCIES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${DEPENDENCIES_DIR_NAME})

add_subdirectory(dependencies/glfw-3.3.7)
add_subdirectory(Lib/core/Utils)
add_subdirectory(Lib/core/Wrappers)
add_subdirectory(Lib/core/Objects)
add_subdirectory(Lib/glad)
add_subdirectory(Lib/glew)
add_subdirectory(Lib/glm)

add_executable(SeNes2D
        main.cpp
)

target_link_libraries(SeNes2D PUBLIC
        glfw
        Wrappers
        Objects
)

target_include_directories(SeNes2D PUBLIC
        Lib/core/Wrappers/include/Window.h
)

include(cmake/Deploy.cmake)
MyDeploy(SeNes2D)