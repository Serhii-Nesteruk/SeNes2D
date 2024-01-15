file(
        GLOB ShapesSources
        "includes/*.h"
        "sources/*.cpp"
)

add_library(Shapes ${ShapesSources})

target_link_libraries(Shapes PUBLIC Wrappers)

target_include_directories(Shapes PUBLIC
        includes
        ../../Wrappers/include
        ../../../../dependencies/GLM
        ../includes
)