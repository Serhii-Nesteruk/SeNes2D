#pragma once

#include <filesystem>

namespace Utils {
    [[maybe_unused]] [[nodiscard]] std::string getFileContent(const std::filesystem::path& path);
}