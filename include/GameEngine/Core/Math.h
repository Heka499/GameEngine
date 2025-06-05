#pragma once
#include <cmath>
#include <iostream>

namespace GameEngine {
namespace Math {

class Vector2 {
public:
    float x, y;

    Vector2() : x(0.0f), y(0.0f) {}
    Vector2(float x, float y) : x(x), y(y) {}

    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(float scalar) const;
    Vector2 operator+=(const Vector2& other);

    float Magnitude() const;
    float MagnitudeSquared() const;
    Vector2 Normalized() const;
    float Dot(const Vector2& other) const;
};

class Vector3 {
public:
    float x, y, z;

    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator*(float scalar) const;
    Vector3 operator+=(const Vector3& other);

    float Magnitude() const;
    Vector3 Normalized() const;
    float Dot(const Vector3& other) const;
    Vector3 Cross(const Vector3& other) const;
};

class Matrix4 {
private:
    float m[16];
public:
    Matrix4();
    Matrix4(float diagonal);

    static Matrix4 Identity();
    static Matrix4 Translation(const Vector3& translation);
    static Matrix4 Scale(const Vector3& scale);
    static Matrix4 RotationX(float angle);
    static Matrix4 RotationY(float angle);
    static Matrix4 RotationZ(float angle);

    Matrix4 operator*(const Matrix4& other) const;
    Vector3 operator*(const Vector3& vector) const;

    float* Data() { return m; }
    const float* Data() const { return m; }
};

}}