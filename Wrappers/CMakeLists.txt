file(
        GLOB WrappersSources
        "include/*.h"
        "source/*.cpp"
)

add_library(Wrappers ${WrappersSources})

target_link_libraries(Wrappers
        PUBLIC
        MyUtils
)

target_include_directories(Wrappers
        PUBLIC
        ./include
)