#pragma once
#include <gtest/gtest.h>
#include <cmath>

// Custom assertion for floating point comparisons with epsilon
#define EXPECT_VEC2_EQ(v1, v2) \
    do { \
        EXPECT_FLOAT_EQ((v1).x, (v2).x); \
        EXPECT_FLOAT_EQ((v1).y, (v2).y); \
    } while (0)

#define EXPECT_VEC3_EQ(v1, v2) \
    do { \
        EXPECT_FLOAT_EQ((v1).x, (v2).x); \
        EXPECT_FLOAT_EQ((v1).y, (v2).y); \
        EXPECT_FLOAT_EQ((v1).z, (v2).z); \
    } while (0)

// Helper function to create temporary test files
class TempFile {
private:
    std::string filename;

public:
    TempFile(const std::string& name) : filename(name) {}

    ~TempFile() {
        std::remove(filename.c_str());
    }

    const std::string& GetName() const { return filename; }
};