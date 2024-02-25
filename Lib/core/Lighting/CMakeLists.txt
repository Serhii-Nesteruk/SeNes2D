file(
        GLOB sources
        "include/*.h"
        "source/*.cpp"
)

add_library(Lighting ${sources})

set_target_properties(Lighting PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(Lighting PUBLIC include)