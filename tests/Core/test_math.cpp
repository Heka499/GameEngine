#include <gtest/gtest.h>
#include "GameEngine/Core/Math.h"
#include <cmath>

using namespace GameEngine::Math;

// Test fixture for Vector2 tests
class Vector2Test : public ::testing::Test {
protected:
    void SetUp() override {
        v1 = Vector2(3.0f, 4.0f);
        v2 = Vector2(1.0f, 2.0f);
        zero = Vector2(0.0f, 0.0f);
    }

    Vector2 v1, v2, zero;
};

TEST_F(Vector2Test, Construction) {
    EXPECT_FLOAT_EQ(v1.x, 3.0f);
    EXPECT_FLOAT_EQ(v1.y, 4.0f);
    EXPECT_FLOAT_EQ(zero.x, 0.0f);
    EXPECT_FLOAT_EQ(zero.y, 0.0f);
}

TEST_F(Vector2Test, Addition) {
    Vector2 result = v1 + v2;
    EXPECT_FLOAT_EQ(result.x, 4.0f);
    EXPECT_FLOAT_EQ(result.y, 6.0f);
}

TEST_F(Vector2Test, Subtraction) {
    Vector2 result = v1 - v2;
    EXPECT_FLOAT_EQ(result.x, 2.0f);
    EXPECT_FLOAT_EQ(result.y, 2.0f);
}

TEST_F(Vector2Test, ScalarMultiplication) {
    Vector2 result = v1 * 2.0f;
    EXPECT_FLOAT_EQ(result.x, 6.0f);
    EXPECT_FLOAT_EQ(result.y, 8.0f);
}

TEST_F(Vector2Test, Magnitude) {
    EXPECT_FLOAT_EQ(v1.Magnitude(), 5.0f); // 3^2 + 4^2 = 25, sqrt(25) = 5
    EXPECT_FLOAT_EQ(zero.Magnitude(), 0.0f);
}

TEST_F(Vector2Test, MagnitudeSquared) {
    EXPECT_FLOAT_EQ(v1.MagnitudeSquared(), 25.0f);
    EXPECT_FLOAT_EQ(zero.MagnitudeSquared(), 0.0f);
}

TEST_F(Vector2Test, Normalization) {
    Vector2 normalized = v1.Normalized();
    EXPECT_FLOAT_EQ(normalized.Magnitude(), 1.0f);
    EXPECT_FLOAT_EQ(normalized.x, 0.6f);  // 3/5
    EXPECT_FLOAT_EQ(normalized.y, 0.8f);  // 4/5
}

TEST_F(Vector2Test, DotProduct) {
    float dot = v1.Dot(v2);
    EXPECT_FLOAT_EQ(dot, 11.0f); // 3*1 + 4*2 = 11
}

TEST_F(Vector2Test, CompoundAssignment) {
    Vector2 result = v1;
    result += v2;
    EXPECT_FLOAT_EQ(result.x, 4.0f);
    EXPECT_FLOAT_EQ(result.y, 6.0f);
}

// Vector3 Tests
class Vector3Test : public ::testing::Test {
protected:
    void SetUp() override {
        v1 = Vector3(1.0f, 2.0f, 3.0f);
        v2 = Vector3(4.0f, 5.0f, 6.0f);
        unitX = Vector3(1.0f, 0.0f, 0.0f);
        unitY = Vector3(0.0f, 1.0f, 0.0f);
        unitZ = Vector3(0.0f, 0.0f, 1.0f);
    }

    Vector3 v1, v2, unitX, unitY, unitZ;
};

TEST_F(Vector3Test, CrossProduct) {
    Vector3 cross = unitX.Cross(unitY);
    EXPECT_FLOAT_EQ(cross.x, 0.0f);
    EXPECT_FLOAT_EQ(cross.y, 0.0f);
    EXPECT_FLOAT_EQ(cross.z, 1.0f);
    
    // Test that cross product is anticommutative
    Vector3 cross2 = unitY.Cross(unitX);
    EXPECT_FLOAT_EQ(cross2.z, -1.0f);
}

TEST_F(Vector3Test, Magnitude) {
    Vector3 v(3.0f, 4.0f, 0.0f);
    EXPECT_FLOAT_EQ(v.Magnitude(), 5.0f);
}

// Matrix4 Tests
class Matrix4Test : public ::testing::Test {
protected:
    void SetUp() override {
        identity = Matrix4::Identity();
        translation = Matrix4::Translation(Vector3(1.0f, 2.0f, 3.0f));
        scale = Matrix4::Scale(Vector3(2.0f, 3.0f, 4.0f));
    }

    Matrix4 identity, translation, scale;
};

TEST_F(Matrix4Test, Identity) {
    // Test that identity matrix doesn't change vectors
    Vector3 testVec(1.0f, 2.0f, 3.0f);
    Vector3 result = identity * testVec;
    
    EXPECT_FLOAT_EQ(result.x, testVec.x);
    EXPECT_FLOAT_EQ(result.y, testVec.y);
    EXPECT_FLOAT_EQ(result.z, testVec.z);
}

TEST_F(Matrix4Test, Translation) {
    Vector3 point(0.0f, 0.0f, 0.0f);
    Vector3 translated = translation * point;
    
    EXPECT_FLOAT_EQ(translated.x, 1.0f);
    EXPECT_FLOAT_EQ(translated.y, 2.0f);
    EXPECT_FLOAT_EQ(translated.z, 3.0f);
}

TEST_F(Matrix4Test, Scale) {
    Vector3 point(1.0f, 1.0f, 1.0f);
    Vector3 scaled = scale * point;
    
    EXPECT_FLOAT_EQ(scaled.x, 2.0f);
    EXPECT_FLOAT_EQ(scaled.y, 3.0f);
    EXPECT_FLOAT_EQ(scaled.z, 4.0f);
}

TEST_F(Matrix4Test, MatrixMultiplication) {
    Matrix4 result = translation * scale;
    Vector3 point(1.0f, 1.0f, 1.0f);
    Vector3 transformed = result * point;
    
    // Should scale first, then translate
    EXPECT_FLOAT_EQ(transformed.x, 3.0f); // 1*2 + 1 = 3
    EXPECT_FLOAT_EQ(transformed.y, 5.0f); // 1*3 + 2 = 5
    EXPECT_FLOAT_EQ(transformed.z, 7.0f); // 1*4 + 3 = 7
}