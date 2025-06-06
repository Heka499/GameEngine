#include "GameEngine/Core/Math.h"

namespace GameEngine {
namespace Math {

Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
Vector3::Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

Vector3 Vector3::operator+(const Vector3& other) const {
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other) const {
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(float scalar) const {
    return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 Vector3::operator+=(const Vector3& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

bool Vector3::operator==(const Vector3& other) const {
    return (x == other.x && y == other.y && z == other.z);
}

bool Vector3::operator!=(const Vector3& other) const {
    return !(*this == other);
}

float Vector3::Magnitude() const {
    return std::sqrt(x * x + y * y + z * z);
}

float Vector3::length() const {
    return Magnitude(); // Alias for Magnitude
}

Vector3 Vector3::Normalized() const {
    float mag = Magnitude();
    if (mag == 0) return Vector3(0, 0, 0); // Avoid division by zero
    return Vector3(x / mag, y / mag, z / mag);
}

float Vector3::Dot(const Vector3& other) const {
    return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::Cross(const Vector3& other) const {
    return Vector3(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

} // namespace Math
} // namespace GameEngine