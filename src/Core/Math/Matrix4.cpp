#include "GameEngine/Core/Math.h"
#include <cmath>
#include <cstring>

namespace GameEngine {
namespace Math {

Matrix4::Matrix4() {
    std::memset(m, 0, sizeof(m));
    m[0] = m[5] = m[10] = m[15] = 1.0f; // Identity matrix
}

Matrix4::Matrix4(const float values[16]) {
    std::memcpy(m, values, sizeof(m));
}

Matrix4 Matrix4::identity() {
    return Matrix4();
}

Matrix4 Matrix4::translation(float x, float y, float z) {
    Matrix4 result;
    result.m[12] = x; // Column 3, Row 0
    result.m[13] = y; // Column 3, Row 1
    result.m[14] = z; // Column 3, Row 2
    return result;
}

Matrix4 Matrix4::translation(const Vector3& position) {
    return translation(position.x, position.y, position.z);
}

Matrix4 Matrix4::scale(float x, float y, float z) {
    Matrix4 result;
    result.m[0] = x; // Scale X
    result.m[5] = y; // Scale Y
    result.m[10] = z; // Scale Z
    return result;
}

Matrix4 Matrix4::scale(const Vector3& scale) {
    return Matrix4::scale(scale.x, scale.y, scale.z);
}

Matrix4 Matrix4::scale(float uniform) {
    return scale(uniform, uniform, uniform);
}

Matrix4 Matrix4::rotationX(float angle) {
    Matrix4 result;
    float c = std::cos(angle);
    float s = std::sin(angle);
    result.m[5] = c; // cos(angle)
    result.m[6] = -s; // -sin(angle)
    result.m[9] = s; // sin(angle)
    result.m[10] = c; // cos(angle)
    return result;
}

Matrix4 Matrix4::rotationY(float angle) {
    Matrix4 result;
    float c = std::cos(angle);
    float s = std::sin(angle);
    result.m[0] = c; // cos(angle)
    result.m[2] = s; // sin(angle)
    result.m[8] = -s; // -sin(angle)
    result.m[10] = c; // cos(angle)
    return result;
}

Matrix4 Matrix4::rotationZ(float angle) {
    Matrix4 result;
    float c = std::cos(angle);
    float s = std::sin(angle);
    result.m[0] = c; // cos(angle)
    result.m[1] = -s; // -sin(angle)
    result.m[4] = s; // sin(angle)
    result.m[5] = c; // cos(angle)
    return result;
}

Matrix4 Matrix4::operator*(const Matrix4& other) const {
    Matrix4 result;

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            float sum = 0.0f;
            for (int k = 0; k < 4; ++k) {
                sum += m[row + k * 4] * other.m[k + col * 4];
            }
            result.m[row + col * 4] = sum;
        }
    }
    return result;
}

float& Matrix4::operator()(int row, int col) {
    return m[row + col * 4];
}

const float& Matrix4::operator()(int row, int col) const {
    return m[row + col * 4];
}

float* Matrix4::data() {
    return m;
}

const float* Matrix4::data() const {
    return m;
}

Vector3 Matrix4::transformPoint(const Vector3& point) const {
    float x = m[0] * point.x + m[4] * point.y + m[8] * point.z + m[12];
    float y = m[1] * point.x + m[5] * point.y + m[9] * point.z + m[13];
    float z = m[2] * point.x + m[6] * point.y + m[10] * point.z + m[14];
    return Vector3(x, y, z);
}

Vector3 Matrix4::transformDirection(const Vector3& direction) const {
    float x = m[0] * direction.x + m[4] * direction.y + m[8] * direction.z;
    float y = m[1] * direction.x + m[5] * direction.y + m[9] * direction.z;
    float z = m[2] * direction.x + m[6] * direction.y + m[10] * direction.z;
    return Vector3(x, y, z);
}

} // namespace Math
} // namespace GameEngine