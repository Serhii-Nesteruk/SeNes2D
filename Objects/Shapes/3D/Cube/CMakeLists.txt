file(
        GLOB CubeSources
        "include/*.h"
        "source/*.cpp"
)

add_library(Cube ${CubeSources})
target_include_directories(Cube PUBLIC ./include)