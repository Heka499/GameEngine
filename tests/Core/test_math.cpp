#include <gtest/gtest.h>
#include "GameEngine/Core/Math.h"
#include <cmath>
#include <cstring>

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
// Helper function for floating-point comparisons
// Matrices involve lots of floating-point math, so we need epsilon comparisons
const float EPSILON = 1e-6f;

bool isEqual(float a, float b, float epsilon = EPSILON) {
    return std::abs(a - b) < epsilon;
}

bool matricesEqual(const Matrix4& a, const Matrix4& b, float epsilon = EPSILON) {
    for (int i = 0; i < 16; ++i) {
        if (!isEqual(a.m[i], b.m[i], epsilon)) {
            return false;
        }
    }
    return true;
}

bool vectorsEqual(const Vector3& a, const Vector3& b, float epsilon = EPSILON) {
    return isEqual(a.x, b.x, epsilon) && 
           isEqual(a.y, b.y, epsilon) && 
           isEqual(a.z, b.z, epsilon);
}

// Test fixture for Matrix4 tests
class Matrix4Test : public ::testing::Test {
protected:
    void SetUp() override {
        // Common test data setup
        identityValues[0] = identityValues[5] = identityValues[10] = identityValues[15] = 1.0f;
        for (int i = 0; i < 16; ++i) {
            if (i != 0 && i != 5 && i != 10 && i != 15) {
                identityValues[i] = 0.0f;
            }
        }
    }

    float identityValues[16] = {0};
};

// ========== IDENTITY MATRIX TESTS ==========
TEST_F(Matrix4Test, DefaultConstructorCreatesIdentity) {
    Matrix4 mat;
    
    // Check diagonal elements are 1
    EXPECT_FLOAT_EQ(mat(0, 0), 1.0f);
    EXPECT_FLOAT_EQ(mat(1, 1), 1.0f);
    EXPECT_FLOAT_EQ(mat(2, 2), 1.0f);
    EXPECT_FLOAT_EQ(mat(3, 3), 1.0f);
    
    // Check off-diagonal elements are 0
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (row != col) {
                EXPECT_FLOAT_EQ(mat(row, col), 0.0f);
            }
        }
    }
}

TEST_F(Matrix4Test, IdentityFunctionCreatesIdentity) {
    Matrix4 identity = Matrix4::identity();
    Matrix4 defaultMat;
    
    EXPECT_TRUE(matricesEqual(identity, defaultMat));
}

TEST_F(Matrix4Test, IdentityMultiplicationDoesNothing) {
    Matrix4 identity = Matrix4::identity();
    Matrix4 testMatrix = Matrix4::translation(5, 3, 2);
    
    Matrix4 result1 = identity * testMatrix;
    Matrix4 result2 = testMatrix * identity;
    
    EXPECT_TRUE(matricesEqual(result1, testMatrix));
    EXPECT_TRUE(matricesEqual(result2, testMatrix));
}

// ========== TRANSLATION MATRIX TESTS ==========
TEST_F(Matrix4Test, TranslationMatrixCreation) {
    Matrix4 trans = Matrix4::translation(5.0f, 3.0f, -2.0f);
    
    // Translation values should be in column 3
    EXPECT_FLOAT_EQ(trans(0, 3), 5.0f);  // X translation
    EXPECT_FLOAT_EQ(trans(1, 3), 3.0f);  // Y translation  
    EXPECT_FLOAT_EQ(trans(2, 3), -2.0f); // Z translation
    
    // Rest should be identity
    EXPECT_FLOAT_EQ(trans(0, 0), 1.0f);
    EXPECT_FLOAT_EQ(trans(1, 1), 1.0f);
    EXPECT_FLOAT_EQ(trans(2, 2), 1.0f);
    EXPECT_FLOAT_EQ(trans(3, 3), 1.0f);
    
    // Off-diagonal (except translation column) should be 0
    EXPECT_FLOAT_EQ(trans(0, 1), 0.0f);
    EXPECT_FLOAT_EQ(trans(1, 0), 0.0f);
    EXPECT_FLOAT_EQ(trans(2, 1), 0.0f);
}

TEST_F(Matrix4Test, TranslationWithVector3) {
    Vector3 pos(10.0f, -5.0f, 7.0f);
    Matrix4 trans1 = Matrix4::translation(pos);
    Matrix4 trans2 = Matrix4::translation(10.0f, -5.0f, 7.0f);
    
    EXPECT_TRUE(matricesEqual(trans1, trans2));
}

TEST_F(Matrix4Test, TranslationTransformsPoints) {
    Matrix4 trans = Matrix4::translation(3.0f, 4.0f, 5.0f);
    Vector3 point(1.0f, 2.0f, 3.0f);
    
    Vector3 result = trans.transformPoint(point);
    Vector3 expected(4.0f, 6.0f, 8.0f); // Original + translation
    
    EXPECT_TRUE(vectorsEqual(result, expected));
}

TEST_F(Matrix4Test, TranslationDoesNotAffectDirections) {
    Matrix4 trans = Matrix4::translation(10.0f, 20.0f, 30.0f);
    Vector3 direction(1.0f, 0.0f, 0.0f);
    
    Vector3 result = trans.transformDirection(direction);
    
    EXPECT_TRUE(vectorsEqual(result, direction)); // Should be unchanged
}

// ========== SCALE MATRIX TESTS ==========
TEST_F(Matrix4Test, ScaleMatrixCreation) {
    Matrix4 scale = Matrix4::scale(2.0f, 3.0f, 0.5f);
    
    // Scale values should be on diagonal  
    EXPECT_FLOAT_EQ(scale(0, 0), 2.0f);
    EXPECT_FLOAT_EQ(scale(1, 1), 3.0f);
    EXPECT_FLOAT_EQ(scale(2, 2), 0.5f);
    EXPECT_FLOAT_EQ(scale(3, 3), 1.0f);
    
    // Off-diagonal should be 0
    EXPECT_FLOAT_EQ(scale(0, 1), 0.0f);
    EXPECT_FLOAT_EQ(scale(1, 0), 0.0f);
    EXPECT_FLOAT_EQ(scale(0, 3), 0.0f);
}

TEST_F(Matrix4Test, UniformScaleCreation) {
    Matrix4 scale1 = Matrix4::scale(2.5f);
    Matrix4 scale2 = Matrix4::scale(2.5f, 2.5f, 2.5f);
    
    EXPECT_TRUE(matricesEqual(scale1, scale2));
}

TEST_F(Matrix4Test, ScaleWithVector3) {
    Vector3 scaleVec(0.5f, 2.0f, 1.5f);
    Matrix4 scale1 = Matrix4::scale(scaleVec);
    Matrix4 scale2 = Matrix4::scale(0.5f, 2.0f, 1.5f);
    
    EXPECT_TRUE(matricesEqual(scale1, scale2));
}

TEST_F(Matrix4Test, ScaleTransformsPoints) {
    Matrix4 scale = Matrix4::scale(2.0f, 0.5f, 3.0f);
    Vector3 point(4.0f, 6.0f, 2.0f);
    
    Vector3 result = scale.transformPoint(point);
    Vector3 expected(8.0f, 3.0f, 6.0f); // Each component scaled
    
    EXPECT_TRUE(vectorsEqual(result, expected));
}

TEST_F(Matrix4Test, ScaleTransformsDirections) {
    Matrix4 scale = Matrix4::scale(2.0f, 3.0f, 0.5f);
    Vector3 direction(1.0f, 1.0f, 2.0f);
    
    Vector3 result = scale.transformDirection(direction);
    Vector3 expected(2.0f, 3.0f, 1.0f);
    
    EXPECT_TRUE(vectorsEqual(result, expected));
}

// ========== ROTATION MATRIX TESTS ==========
TEST_F(Matrix4Test, RotationXCreation) {
    float angle = M_PI / 4.0f; // 45 degrees
    Matrix4 rot = Matrix4::rotationX(angle);
    
    float c = std::cos(angle);
    float s = std::sin(angle);
    
    // X rotation affects Y and Z components
    EXPECT_FLOAT_EQ(rot(0, 0), 1.0f);  // X unchanged
    EXPECT_TRUE(isEqual(rot(1, 1), c));   // cos
    EXPECT_TRUE(isEqual(rot(1, 2), -s));  // -sin
    EXPECT_TRUE(isEqual(rot(2, 1), s));   // sin  
    EXPECT_TRUE(isEqual(rot(2, 2), c));   // cos
    EXPECT_FLOAT_EQ(rot(3, 3), 1.0f);
}

TEST_F(Matrix4Test, RotationYCreation) {
    float angle = M_PI / 6.0f; // 30 degrees
    Matrix4 rot = Matrix4::rotationY(angle);
    
    float c = std::cos(angle);
    float s = std::sin(angle);
    
    // Y rotation affects X and Z components
    EXPECT_TRUE(isEqual(rot(0, 0), c));   // cos
    EXPECT_TRUE(isEqual(rot(0, 2), s));   // sin
    EXPECT_FLOAT_EQ(rot(1, 1), 1.0f);     // Y unchanged
    EXPECT_TRUE(isEqual(rot(2, 0), -s));  // -sin
    EXPECT_TRUE(isEqual(rot(2, 2), c));   // cos
}

TEST_F(Matrix4Test, RotationZCreation) {
    float angle = M_PI / 3.0f; // 60 degrees
    Matrix4 rot = Matrix4::rotationZ(angle);
    
    float c = std::cos(angle);
    float s = std::sin(angle);
    
    // Z rotation affects X and Y components
    EXPECT_TRUE(isEqual(rot(0, 0), c));   // cos
    EXPECT_TRUE(isEqual(rot(0, 1), -s));  // -sin
    EXPECT_TRUE(isEqual(rot(1, 0), s));   // sin
    EXPECT_TRUE(isEqual(rot(1, 1), c));   // cos
    EXPECT_FLOAT_EQ(rot(2, 2), 1.0f);     // Z unchanged
}

TEST_F(Matrix4Test, Rotation90DegreesKnownValues) {
    float angle90 = M_PI / 2.0f;
    
    // 90-degree rotation around Z should turn (1,0,0) into (0,1,0)
    Matrix4 rotZ90 = Matrix4::rotationZ(angle90);
    Vector3 xAxis(1.0f, 0.0f, 0.0f);
    Vector3 result = rotZ90.transformDirection(xAxis);
    Vector3 expected(0.0f, 1.0f, 0.0f);
    
    EXPECT_TRUE(vectorsEqual(result, expected, 1e-5f));
}

TEST_F(Matrix4Test, RotationPreservesLength) {
    Matrix4 rot = Matrix4::rotationY(M_PI / 7.0f); // Random angle
    Vector3 vector(3.0f, 4.0f, 5.0f);
    
    float originalLength = vector.magnitude();
    Vector3 rotated = rot.transformDirection(vector);
    float rotatedLength = rotated.magnitude();
    
    EXPECT_TRUE(isEqual(originalLength, rotatedLength, 1e-5f));
}

// ========== MATRIX MULTIPLICATION TESTS ==========
TEST_F(Matrix4Test, MatrixMultiplicationBasic) {
    Matrix4 trans = Matrix4::translation(1.0f, 2.0f, 3.0f);
    Matrix4 scale = Matrix4::scale(2.0f, 2.0f, 2.0f);
    
    Matrix4 combined = trans * scale;
    
    // Apply to a test point
    Vector3 point(1.0f, 1.0f, 1.0f);
    Vector3 result = combined.transformPoint(point);
    
    // Should scale first (2,2,2) then translate (+1,+2,+3) = (3,4,5)
    Vector3 expected(3.0f, 4.0f, 5.0f);
    EXPECT_TRUE(vectorsEqual(result, expected));
}

TEST_F(Matrix4Test, MultiplicationOrderMatters) {
    Matrix4 trans = Matrix4::translation(5.0f, 0.0f, 0.0f);
    Matrix4 scale = Matrix4::scale(2.0f, 1.0f, 1.0f);
    
    Matrix4 scaleFirst = trans * scale;
    Matrix4 transFirst = scale * trans;
    
    Vector3 point(1.0f, 0.0f, 0.0f);
    Vector3 result1 = scaleFirst.transformPoint(point);  // Scale then translate
    Vector3 result2 = transFirst.transformPoint(point);  // Translate then scale
    
    EXPECT_FALSE(vectorsEqual(result1, result2));
    
    // Verify specific results
    Vector3 expected1(7.0f, 0.0f, 0.0f); // Scale to 2, then +5 = 7
    Vector3 expected2(12.0f, 0.0f, 0.0f); // Translate to 6, then *2 = 12
    
    EXPECT_TRUE(vectorsEqual(result1, expected1));
    EXPECT_TRUE(vectorsEqual(result2, expected2));
}

TEST_F(Matrix4Test, ComplexTransformationChain) {
    // Create a complex transformation: Scale -> Rotate -> Translate
    Vector3 point(1.0f, 0.0f, 0.0f);
    
    Matrix4 scale = Matrix4::scale(2.0f, 2.0f, 2.0f);
    Matrix4 rotate = Matrix4::rotationZ(M_PI / 2.0f); // 90 degrees
    Matrix4 translate = Matrix4::translation(10.0f, 5.0f, 0.0f);
    
    Matrix4 combined = translate * rotate * scale;
    Vector3 result = combined.transformPoint(point);
    
    // Manual calculation:
    // 1. Scale: (1,0,0) -> (2,0,0)
    // 2. Rotate 90° around Z: (2,0,0) -> (0,2,0)  
    // 3. Translate: (0,2,0) -> (10,7,0)
    Vector3 expected(10.0f, 7.0f, 0.0f);
    
    EXPECT_TRUE(vectorsEqual(result, expected, 1e-5f));
}

// ========== ELEMENT ACCESS TESTS ==========
TEST_F(Matrix4Test, ElementAccess) {
    Matrix4 mat;
    
    // Test setting and getting elements
    mat(1, 2) = 42.0f;
    EXPECT_FLOAT_EQ(mat(1, 2), 42.0f);
    
    // Test const access
    const Matrix4& constMat = mat;
    EXPECT_FLOAT_EQ(constMat(1, 2), 42.0f);
}

TEST_F(Matrix4Test, ArrayConstructor) {
    float values[16] = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16
    };
    
    Matrix4 mat(values);
    
    // Test that values are stored correctly (column-major)
    EXPECT_FLOAT_EQ(mat.data[0], 1.0f);
    EXPECT_FLOAT_EQ(mat.data[4], 5.0f);
    EXPECT_FLOAT_EQ(mat.data[15], 16.0f);
}

// ========== EDGE CASES AND ERROR CONDITIONS ==========
TEST_F(Matrix4Test, ZeroScaleHandling) {
    Matrix4 zeroScale = Matrix4::scale(0.0f, 1.0f, 1.0f);
    Vector3 point(5.0f, 3.0f, 2.0f);
    
    Vector3 result = zeroScale.transformPoint(point);
    
    EXPECT_FLOAT_EQ(result.x, 0.0f); // X component should be zero
    EXPECT_FLOAT_EQ(result.y, 3.0f); // Y should be unchanged
    EXPECT_FLOAT_EQ(result.z, 2.0f); // Z should be unchanged
}

TEST_F(Matrix4Test, VerySmallRotation) {
    float tinyAngle = 1e-7f;
    Matrix4 rot = Matrix4::rotationX(tinyAngle);
    
    // Should be very close to identity
    Matrix4 identity = Matrix4::identity();
    EXPECT_TRUE(matricesEqual(rot, identity, 1e-6f));
}

TEST_F(Matrix4Test, FullCircleRotation) {
    float fullCircle = 2.0f * M_PI;
    Matrix4 rot = Matrix4::rotationY(fullCircle);
    
    Vector3 point(1.0f, 2.0f, 3.0f);
    Vector3 result = rot.transformPoint(point);
    
    // Should be back to original (within floating-point precision)
    EXPECT_TRUE(vectorsEqual(result, point, 1e-5f));
}

// ========== PERFORMANCE/STRESS TESTS ==========
TEST_F(Matrix4Test, ManyMultiplications) {
    Matrix4 result = Matrix4::identity();
    Matrix4 smallRot = Matrix4::rotationZ(0.01f); // Small rotation
    
    // Apply many small rotations
    for (int i = 0; i < 100; ++i) {
        result = result * smallRot;
    }
    
    // Total rotation should be 1 radian
    Matrix4 expected = Matrix4::rotationZ(1.0f);
    EXPECT_TRUE(matricesEqual(result, expected, 1e-3f)); // Looser tolerance due to accumulation
}