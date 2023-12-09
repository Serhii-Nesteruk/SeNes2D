file(
        GLOB SOURCE
        "include/*.h"
        "source/*.cpp"
)

add_library(WorldObject3D ${SOURCE})

target_include_directories(WorldObject3D PUBLIC ./include)