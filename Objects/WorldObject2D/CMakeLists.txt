file(
        GLOB SOURCE
        "include/*.h"
        "source/*.cpp"
)

add_library(WorldObject2D ${SOURCE})

target_include_directories(WorldObject2D PUBLIC ./include)