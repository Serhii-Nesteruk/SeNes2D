file(
        GLOB SOURCE
        "include/*.h"
        "source/*.cpp"
)

add_library(MyUtils ${SOURCE})

target_include_directories(MyUtils PUBLIC include)