file(
        GLOB WrappersSources
        "include/*.h"
        "source/*.cpp"
)

add_library(Wrappers ${WrappersSources})

target_link_libraries(Wrappers
        PUBLIC
        MyUtils
        Glew
        Glad
        Glm
)

target_include_directories(Wrappers
        PUBLIC
        include
        ../../../dependencies/glfw-3.3.7/include
)