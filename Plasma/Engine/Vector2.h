// By @ByCubed7 on Twitter

#pragma once

#include <iostream>
#include <string>

// A two dimensional vector. Attempted translatation from Unity C#
struct Vector2 
{
    // (Structs are public by default)

    // - Static Properties

    static const Vector2 up;
    static const Vector2 down;
    static const Vector2 left;
    static const Vector2 right;
    static const Vector2 one;
    static const Vector2 zero;


    // - Properties

    float x;
    float y;


    // - Constructors

    Vector2();
    Vector2(float coordX, float coordY);
    Vector2(const Vector2& oldVector2);
    Vector2(const int coord);
    //~Vector2();

    // - Methods

    float Magnitude();
    void Normalize();
    void Negate();
    void Set(float newX, float newY);
    std::string ToString();

    // - Static Methods

    static float Angle(Vector2 from, Vector2 to);
    static Vector2 ClampMagnitude(Vector2 vector, float maxLength);
    static float Distance(Vector2 from, Vector2 to);
    static float Dot(Vector2 vectorA, Vector2 vectorB);
    static Vector2 Lerp(Vector2 vectorA, Vector2 vectorB, float point);
    static Vector2 Max(Vector2 vectorA, Vector2 vectorB);
    static Vector2 Min(Vector2 vectorA, Vector2 vectorB);


    // - Operators

    // Vector

    Vector2 operator+(const Vector2& otherVector);
    Vector2 operator-(const Vector2& otherVector);
    Vector2 operator*(const Vector2& otherVector);
    Vector2 operator/(const Vector2& otherVector);
    Vector2 operator+=(const Vector2& otherVector);
    Vector2 operator-=(const Vector2& otherVector);
    Vector2 operator*=(const Vector2& otherVector);
    Vector2 operator/=(const Vector2& otherVector);

    // Float

    Vector2 operator+(const float& otherVector);
    Vector2 operator-(const float& otherVector);
    Vector2 operator*(const float& otherVector);
    Vector2 operator/(const float& otherVector);
    Vector2 operator+=(const float& otherVector);
    Vector2 operator-=(const float& otherVector);
    Vector2 operator*=(const float& otherVector);
    Vector2 operator/=(const float& otherVector);

    // Float

    Vector2 operator+(const int& otherVector);
    Vector2 operator-(const int& otherVector);
    Vector2 operator*(const int& otherVector);
    Vector2 operator/(const int& otherVector);
    Vector2 operator+=(const int& otherVector);
    Vector2 operator-=(const int& otherVector);
    Vector2 operator*=(const int& otherVector);
    Vector2 operator/=(const int& otherVector);

};