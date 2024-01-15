file(
        GLOB ObjectsSources
        "includes/*.h"
        "sources/*.cpp"
)

add_subdirectory(Shapes)

add_library(Objects ${ObjectsSources})

target_include_directories(Objects PUBLIC
        includes
        ../Wrappers/include
        ../../../dependencies/GLM
)

target_link_libraries(Objects PUBLIC Shapes)