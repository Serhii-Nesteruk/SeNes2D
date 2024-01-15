#include "../include/Utils.h"

#include <fstream>
// clang-format off
#include <Windows.h>
#include <debugapi.h>
//clang-format on

std::string Utils::getFileContent(const std::filesystem::path &path) {
    std::fstream file(path.string());

    if (!file.is_open())
        DebugBreak(); // can't open a file

    std::string content( (std::istreambuf_iterator<char>(file) ),
                         (std::istreambuf_iterator<char>()    ) );

    return content;
}
