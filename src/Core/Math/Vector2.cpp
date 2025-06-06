#include "GameEngine/Core/Math.h"

namespace GameEngine {
namespace Math {

Vector2::Vector2() : x(0.0f), y(0.0f) {}
Vector2::Vector2(float x_, float y_) : x(x_), y(y_) {}

// Add basic implementations
Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

bool Vector2::operator==(const Vector2& other) {
    return (x == other.x && y == other.y);
}

bool Vector2::operator!=(const Vector2& other) {
    return !(*this == other);
}

float Vector2::Magnitude() const {
    return std::sqrt(x * x + y * y);
}

float Vector2::length() const {
    return Magnitude(); // Alias for Magnitude
}

float Vector2::MagnitudeSquared() const {
    return x * x + y * y;
}

Vector2 Vector2::Normalized() const {
    float mag = Magnitude();
    if (mag == 0) return Vector2(0, 0); // Avoid division by zero
    return Vector2(x / mag, y / mag);
}

float Vector2::Dot(const Vector2& other) const {
    return x * other.x + y * other.y;
}

} // namespace Math
} // namespace GameEngine