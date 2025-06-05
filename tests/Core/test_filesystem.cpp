#include <gtest/gtest.h>
#include "GameEngine/Core/FileSystem.h"
#include <fstream>

using namespace GameEngine::Core;

class FileSystemTest : public ::testing::Test {
protected:
    void SetUp() override {
        testTextFile = "test_file.txt";
        testBinaryFile = "test_file.bin";
        testContent = "Hello, World!\nThis is a test file.";
        
        // Clean up any existing test files
        std::remove(testTextFile.c_str());
        std::remove(testBinaryFile.c_str());
    }
    
    void TearDown() override {
        // Clean up test files
        std::remove(testTextFile.c_str());
        std::remove(testBinaryFile.c_str());
    }
    
    std::string testTextFile;
    std::string testBinaryFile;
    std::string testContent;
};

TEST_F(FileSystemTest, TextFileOperations) {
    // Test writing
    EXPECT_TRUE(FileSystem::WriteTextFile(testTextFile, testContent));
    EXPECT_TRUE(FileSystem::FileExists(testTextFile));
    
    // Test reading
    auto readContent = FileSystem::ReadTextFile(testTextFile);
    ASSERT_TRUE(readContent.has_value());
    EXPECT_EQ(readContent.value(), testContent);
}

TEST_F(FileSystemTest, BinaryFileOperations) {
    std::vector<char> binaryData = {'H', 'e', 'l', 'l', 'o', '\0', 0x42, 0xFF};
    
    // Test writing
    EXPECT_TRUE(FileSystem::WriteBinaryFile(testBinaryFile, binaryData));
    EXPECT_TRUE(FileSystem::FileExists(testBinaryFile));
    
    // Test reading
    auto readData = FileSystem::ReadBinaryFile(testBinaryFile);
    ASSERT_TRUE(readData.has_value());
    EXPECT_EQ(readData.value(), binaryData);
}

TEST_F(FileSystemTest, NonExistentFile) {
    // Test reading non-existent file
    auto content = FileSystem::ReadTextFile("nonexistent.txt");
    EXPECT_FALSE(content.has_value());
    
    auto binaryContent = FileSystem::ReadBinaryFile("nonexistent.bin");
    EXPECT_FALSE(binaryContent.has_value());
    
    EXPECT_FALSE(FileSystem::FileExists("nonexistent.txt"));
}

TEST_F(FileSystemTest, PathUtilities) {
    EXPECT_EQ(FileSystem::GetFileExtension("test.txt"), "txt");
    EXPECT_EQ(FileSystem::GetFileExtension("path/to/file.cpp"), "cpp");
    EXPECT_EQ(FileSystem::GetFileExtension("noextension"), "");
    
    EXPECT_EQ(FileSystem::GetFileName("path/to/file.txt"), "file.txt");
    EXPECT_EQ(FileSystem::GetFileName("file.txt"), "file.txt");
    
    EXPECT_EQ(FileSystem::GetDirectoryPath("path/to/file.txt"), "path/to");
    EXPECT_EQ(FileSystem::GetDirectoryPath("file.txt"), "");
}