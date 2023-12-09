file(
        GLOB SOURCE
        "3D/Cube/include/*.h"
        "3D/Cube/source/*.cpp"
)

add_library(Shapes ${SOURCE})

target_include_directories(Shapes PUBLIC ./include)