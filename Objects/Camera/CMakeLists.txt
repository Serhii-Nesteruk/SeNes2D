file(
        GLOB SOURCE
        "include/*.h"
        "source/*.cpp"
)

add_library(Camera ${SOURCE})

target_include_directories(Camera PUBLIC ./include)