//// By @ByCubed7 on Twitter
//
//#pragma once
//
//#include <iostream>
//#include <string>
//
///// <summary>
///// A two dimensional vector. Perhaps inspired from Unity.
///// </summary>
//class Vector2 
//{
//public:
//    // (Structs are public by default)
//
//    // - Static Properties
//
//    static const Vector2 up;
//    static const Vector2 down;
//    static const Vector2 left;
//    static const Vector2 right;
//    static const Vector2 one;
//    static const Vector2 zero;
//
//
//    // - Properties
//
//    float x;
//    float y;
//
//
//    // - Constructors
//
//    Vector2();
//    Vector2(float coordX, float coordY);
//    Vector2(const Vector2& oldVector2);
//    Vector2(const int coord);
//    Vector2(const float coord);
//    //~Vector2();
//
//    // - Methods
//
//    /// <summary>
//    /// The length of the Vector2.
//    /// </summary>
//    /// <returns>The length.</returns>
//    float Magnitude();
//
//    /// <summary>
//    /// Change the length to 1 while keeping direction.
//    /// </summary>
//    void Normalize();
//
//    /// <summary>
//    /// Changes the direction to the exact opposite.
//    /// Just multiply by -1.
//    /// </summary>
//    void Negate();
//
//    /// <summary>
//    /// Set the x and y of the vector.
//    /// </summary>
//    /// <param name="newX">- the new X value.</param>
//    /// <param name="newY">- the new Y value.</param>
//    void Set(float newX, float newY);
//    
//    /// <summary>
//    /// Round the vector to a decimal point
//    /// </summary>
//    /// <param name="dp">- the decimal point. (Defaults to 1)</param>
//    void Round(int dp = 1);
//
//    /// <summary>
//    /// Prints out the vector in string formatting, useful for debugging.
//    /// </summary>
//    /// <returns>A string representation of the vector.</returns>
//    std::string ToString();
//
//    // - Static Methods
//
//    /// <summary>
//    /// Finds the angle between two vectors. <para />
//    /// angle = arccos[(xᵃ * xᵇ + yᵃ * yᵇ) / (√(xᵃ * xᵃ + yᵃ * yᵃ) * √(xᵇ * xᵇ + yᵇ * yᵇ))]
//    /// </summary>
//    /// <param name="from">- the Vector at the starting position</param>
//    /// <param name="to">- the Vector at the ending position</param>
//    /// <returns></returns>
//    static float Angle(Vector2 from, Vector2 to);
//    
//    /// <summary>
//    /// Clamps the vector to  a given length.
//    /// </summary>
//    /// <param name="vector">- the vector to clamp.</param>
//    /// <param name="maxLength">- the max length of the vector to length.</param>
//    /// <returns>The clamped vector.</returns>
//    static Vector2 ClampMagnitude(Vector2 vector, float maxLength);
//
//    /// <summary>
//    /// The distance between two vectors.
//    /// </summary>
//    /// <param name="from">- the vector to start from.</param>
//    /// <param name="to">- the vector to end at.</param>
//    /// <returns></returns>
//    static float Distance(Vector2 from, Vector2 to);
//
//    /// <summary>
//    /// The sum of the products of the corresponding entries of the vectors <para />
//    /// i = 1, nΣaᶦbᶦ
//    /// </summary>
//    /// <param name="vectorA"></param>
//    /// <param name="vectorB"></param>
//    /// <returns></returns>
//    static float Dot(Vector2 vectorA, Vector2 vectorB);
//
//    /// <summary>
//    /// Use linear interpolation between two vectors.
//    /// </summary>
//    /// <param name="vectorA"></param>
//    /// <param name="vectorB"></param>
//    /// <param name="point"></param>
//    /// <returns></returns>
//    static Vector2 Lerp(Vector2 vectorA, Vector2 vectorB, float point);
//
//    /// <summary>
//    /// Returns a vector with the largest components.
//    /// </summary>
//    /// <param name="vectorA">- vector A.</param>
//    /// <param name="vectorB">- vector B.</param>
//    /// <returns>A vector with the largest components.</returns>
//    static Vector2 Max(Vector2 vectorA, Vector2 vectorB);
//
//    /// <summary>
//    /// Returns a vector with the smallest components.
//    /// </summary>
//    /// <param name="vectorA">- vector A.</param>
//    /// <param name="vectorB">- vector B.</param>
//    /// <returns>A vector with the smallest components.</returns>
//    static Vector2 Min(Vector2 vectorA, Vector2 vectorB);
//
//
//    // - Operators
//
//    // Vector
//
//    Vector2 operator+(const Vector2& otherVector);    
//    Vector2 operator-(const Vector2& otherVector);
//    Vector2 operator*(const Vector2& otherVector);
//    Vector2 operator/(const Vector2& otherVector);
//    Vector2 operator+=(const Vector2& otherVector);
//    Vector2 operator-=(const Vector2& otherVector);
//    Vector2 operator*=(const Vector2& otherVector);
//    Vector2 operator/=(const Vector2& otherVector);
//
//    //int cmp(const Vector2& otherVector) const;
//
//    bool operator==(const Vector2& otherVector) const;
//    bool operator!=(const Vector2& otherVector) const;
//    bool operator< (const Vector2& otherVector) const;
//    bool operator> (const Vector2& otherVector) const;
//    //bool operator<=(const Vector2& otherVector) const;
//    //bool operator>=(const Vector2& otherVector) const;
//    
//
//    // Float
//
//    Vector2 operator+(const float& amount);
//    Vector2 operator-(const float& amount);
//    Vector2 operator*(const float& amount);
//    Vector2 operator/(const float& amount);
//    Vector2 operator+=(const float& amount);
//    Vector2 operator-=(const float& amount);
//    Vector2 operator*=(const float& amount);
//    Vector2 operator/=(const float& amount);
//
//    // Int
//
//    Vector2 operator+(const int& amount);
//    Vector2 operator-(const int& amount);
//    Vector2 operator*(const int& amount);
//    Vector2 operator/(const int& amount);
//    Vector2 operator+=(const int& amount);
//    Vector2 operator-=(const int& amount);
//    Vector2 operator*=(const int& amount);
//    Vector2 operator/=(const int& amount);
//
//    //Vector2 operator+(const int& amount) const;
//    //Vector2 operator-(const int& amount) const;
//    //Vector2 operator*(const int& amount) const;
//    //Vector2 operator/(const int& amount) const;
//    //Vector2 operator+=(const int& amount) const;
//    //Vector2 operator-=(const int& amount) const;
//    //Vector2 operator*=(const int& amount) const;
//    //Vector2 operator/=(const int& amount) const;
//
//    // Double
//
//    //Vector2 operator+(const double& amount);
//    //Vector2 operator-(const double& amount);
//    //Vector2 operator*(const double& amount);
//    //Vector2 operator/(const double& amount);
//    //Vector2 operator+=(const double& amount);
//    //Vector2 operator-=(const double& amount);
//    //Vector2 operator*=(const double& amount);
//    //Vector2 operator/=(const double& amount);
//
//};