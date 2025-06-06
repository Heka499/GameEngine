#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <optional>

namespace GameEngine {
namespace Core {

class FileSystem {
public:
    static std::optional<std::string> ReadTextFile(const std::string& filepath);
    static std::optional<std::vector<char>> ReadBinaryFile(const std::string& filepath);
    static bool WriteTextFile(const std::string& filepath, const std::string& content);
    static bool WriteBinaryFile(const std::string& filepath, const std::vector<char>& data);
    static bool FileExists(const std::string& filepath);
    static bool CreateDirectory(const std::string& path);
    static std::string GetFileExtension(const std::string& filepath);
    static std::string GetFileName(const std::string& filepath);
    static std::string GetDirectoryPath(const std::string& filepath);
};

}} // namespace GameEngine::Core