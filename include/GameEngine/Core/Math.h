#pragma once
#include <cmath>
#include <iostream>

namespace GameEngine {
namespace Math {

class Vector2 {
public:
    float x, y;

    Vector2();
    Vector2(float x, float y);

    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(float scalar) const;
    Vector2 operator+=(const Vector2& other);
    bool operator==(const Vector2& other);
    bool operator!=(const Vector2& other);

    float Magnitude() const;
    // length() is an alias for Magnitude
    float length() const;
    float MagnitudeSquared() const;
    Vector2 Normalized() const;
    float Dot(const Vector2& other) const;
    
};

class Vector3 {
public:
    float x, y, z;

    Vector3();
    Vector3(float x, float y, float z);

    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator*(float scalar) const;
    Vector3 operator+=(const Vector3& other);
    bool operator==(const Vector3& other) const;
    bool operator!=(const Vector3& other) const;

    float Magnitude() const;
    float length() const; // Alias for Magnitude
    Vector3 Normalized() const;
    float Dot(const Vector3& other) const;
    Vector3 Cross(const Vector3& other) const;
};

class Matrix4 {
private:
    float m[16];
public:
    Matrix4();
    Matrix4(const float values[16]);

    static Matrix4 identity();
    static Matrix4 translation(float x, float y, float z);
    static Matrix4 translation(const Vector3& position);
    static Matrix4 scale(float x, float y, float z);
    static Matrix4 scale(const Vector3& scale);
    static Matrix4 scale(float uniform);
    static Matrix4 rotationX(float angle);
    static Matrix4 rotationY(float angle);
    static Matrix4 rotationZ(float angle);

    Matrix4 operator*(const Matrix4& other) const;

    float& operator()(int row, int col);
    const float& operator()(int row, int col) const;

    float* data();
    const float* data() const;

    Vector3 transformPoint(const Vector3& point) const;
    Vector3 transformDirection(const Vector3& direction) const;
};

}} // namespace GameEngine::Math