#include "GameEngine/Core/Math.h"

namespace GameEngine {
namespace Math {

Vector2::Vector2() : x(0.0f), y(0.0f) {}
Vector2::Vector2(float x_, float y_) : x(x_), y(y_) {}

// Add basic implementations
Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
}

float Vector2::Magnitude() const {
    return std::sqrt(x * x + y * y);
}

} // namespace Math
} // namespace GameEngine