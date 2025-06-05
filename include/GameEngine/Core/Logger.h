#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

namespace GameEngine {
namespace Core {

enum class LogLevel {
    Debug = 0,
    Info = 1,
    Warning = 2,
    Error = 3
};

class Logger {
private:
    static std::unique_ptr<Logger> instance;
    std::ofstream logFile;
    LogLevel currentLevel;

    Logger();

public:
    static Logger& GetInstance();

    void Initialize(const std::string& filename, LogLevel level = LogLevel::Debug);
    void Log(LogLevel level, const std::string& message);
    void SetLogLevel(LogLevel level) { currentLevel = level; }

    // Convenience methods for different log levels
    void Debug(const std::string& message) { Log(LogLevel::Debug, message); }
    void Info(const std::string& message) { Log(LogLevel::Info, message); }
    void Warning(const std::string& message) { Log(LogLevel::Warning, message); }
    void Error(const std::string& message) { Log(LogLevel::Error, message); }
};

// Macros for easy logging
#define LOG_DEBUG(msg) GameEngine::Core::Logger::GetInstance().Debug(msg)
#define LOG_INFO(msg) GameEngine::Core::Logger::GetInstance().Info(msg)
#define LOG_WARNING(msg) GameEngine::Core::Logger::GetInstance().Warning(msg)
#define LOG_ERROR(msg) GameEngine::Core::Logger::GetInstance().Error(msg)

}} // namespace GameEngine::Core