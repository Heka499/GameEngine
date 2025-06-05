#include <gtest/gtest.h>
#include "GameEngine/Core/Logger.h"
#include <fstream>
#include <sstream>

using namespace GameEngine::Core;

class LoggerTest : public ::testing::Test {
protected:
    void SetUp() override {
        testLogFile = "test_log.txt";
        // Clean up any existing test file
        std::remove(testLogFile.c_str());
    }
    
    void TearDown() override {
        // Clean up test file
        std::remove(testLogFile.c_str());
    }
    
    std::string ReadLogFile() {
        std::ifstream file(testLogFile);
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
    
    std::string testLogFile;
};

TEST_F(LoggerTest, BasicLogging) {
    Logger& logger = Logger::GetInstance();
    logger.Initialize(testLogFile, LogLevel::Debug);
    
    logger.Debug("Debug message");
    logger.Info("Info message");
    logger.Warning("Warning message");
    logger.Error("Error message");
    
    // Force flush by reinitializing or accessing file
    std::string logContent = ReadLogFile();
    
    EXPECT_TRUE(logContent.find("Debug message") != std::string::npos);
    EXPECT_TRUE(logContent.find("Info message") != std::string::npos);
    EXPECT_TRUE(logContent.find("Warning message") != std::string::npos);
    EXPECT_TRUE(logContent.find("Error message") != std::string::npos);
}

TEST_F(LoggerTest, LogLevelFiltering) {
    Logger& logger = Logger::GetInstance();
    logger.Initialize(testLogFile, LogLevel::Warning);
    
    logger.Debug("Debug message");    // Should be filtered out
    logger.Info("Info message");      // Should be filtered out
    logger.Warning("Warning message"); // Should appear
    logger.Error("Error message");     // Should appear
    
    std::string logContent = ReadLogFile();
    
    EXPECT_TRUE(logContent.find("Debug message") == std::string::npos);
    EXPECT_TRUE(logContent.find("Info message") == std::string::npos);
    EXPECT_TRUE(logContent.find("Warning message") != std::string::npos);
    EXPECT_TRUE(logContent.find("Error message") != std::string::npos);
}

TEST_F(LoggerTest, MacroUsage) {
    Logger& logger = Logger::GetInstance();
    logger.Initialize(testLogFile, LogLevel::Debug);
    
    LOG_DEBUG("Macro debug");
    LOG_INFO("Macro info");
    LOG_WARNING("Macro warning");
    LOG_ERROR("Macro error");
    
    std::string logContent = ReadLogFile();
    
    EXPECT_TRUE(logContent.find("Macro debug") != std::string::npos);
    EXPECT_TRUE(logContent.find("Macro info") != std::string::npos);
    EXPECT_TRUE(logContent.find("Macro warning") != std::string::npos);
    EXPECT_TRUE(logContent.find("Macro error") != std::string::npos);
}