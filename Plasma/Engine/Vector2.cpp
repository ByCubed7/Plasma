// By @ByCubed7 on Twitter

#include <iostream>
#include <string>
#include <math.h>

#include "Vector2.h"


// █▀ ▀█▀ ▄▀█ ▀█▀ █ █▀▀   █▀█ █▀█ █▀█ █▀█ █▀▀ █▀█ ▀█▀ █ █▀▀ █▀
// ▄█ ░█░ █▀█ ░█░ █ █▄▄   █▀▀ █▀▄ █▄█ █▀▀ ██▄ █▀▄ ░█░ █ ██▄ ▄█

const Vector2 Vector2::up		= Vector2(0, 1);
const Vector2 Vector2::down		= Vector2(0, -1);
const Vector2 Vector2::left		= Vector2(-1, 0);
const Vector2 Vector2::right	= Vector2(1, 0);
const Vector2 Vector2::one		= Vector2(1, 1);
const Vector2 Vector2::zero		= Vector2(0, 0);


// █▀▀ █▀█ █▄░█ █▀ ▀█▀ █▀█ █░█ █▀▀ ▀█▀ █▀█ █▀█ █▀
// █▄▄ █▄█ █░▀█ ▄█ ░█░ █▀▄ █▄█ █▄▄ ░█░ █▄█ █▀▄ ▄█

// Empty Constructor
Vector2::Vector2() 
{
	x = 0;
	y = 0;
}

// Instance Constructor
Vector2::Vector2(float coordX, float coordY)
{
	x = coordX;
	y = coordY;
}

// Copy Constructor
Vector2::Vector2(const Vector2& oldVector2)
{
	x = oldVector2.x;
	y = oldVector2.y;
}

// Single Int Constructor
Vector2::Vector2(const int coord)
{
	x = coord;
	y = coord;
}


// █▀▄▀█ █▀▀ ▀█▀ █░█ █▀█ █▀▄ █▀
// █░▀░█ ██▄ ░█░ █▀█ █▄█ █▄▀ ▄█

// The length of the Vector2
float Vector2::Magnitude()
{
	// a^2 + b^2 = c^2 
	return sqrt(x * x + y * y);
}

// Change the length to 1 while keeping direction 
void Vector2::Normalize()
{
	float length = Magnitude();

	if (length == 0)
	{
		x = 0;
		y = 0;
		return;
	}

	x = x / length;
	y = y / length;
}

// Direction changes to the exact opposite 
// Just multiply by -1
void Vector2::Negate()
{
	*this *= -1;
}

// Set the x and y of the vector
void Vector2::Set(float newX, float newY)
{
	x = newX;
	y = newY;
}

// Prints out the vector in string formatting, useful for debugging
std::string Vector2::ToString()
{
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}


// █▀ ▀█▀ ▄▀█ ▀█▀ █ █▀▀   █▀▄▀█ █▀▀ ▀█▀ █░█ █▀█ █▀▄ █▀
// ▄█ ░█░ █▀█ ░█░ █ █▄▄   █░▀░█ ██▄ ░█░ █▀█ █▄█ █▄▀ ▄█


// Finds the angle between two vectors
// angle = arccos[(xᵃ * xᵇ + yᵃ * yᵇ) / (√(xᵃ * xᵃ + yᵃ * yᵃ) * √(xᵇ * xᵇ + yᵇ * yᵇ))]
float Vector2::Angle(Vector2 from, Vector2 to)
{
	return acos((from.x * to.y + from.y * to.y) / (from.Magnitude() * to.Magnitude()));
}

// Clamps the vector to  a given length
Vector2 Vector2::ClampMagnitude(Vector2 vector, float maxLength)
{
	Vector2 v = vector; // NOTE: This calls Vector2s copy constructor.. right?
	
	// Compare Taxicab geometry to avoid math.sqrt()
	// from: sqrt(x^2 + b^2) > maxLength 
	// to: x^2 + b^2 > maxLength^2
	if ((v.x * v.x + v.y * v.y) > maxLength * maxLength) {
		v.Normalize();
		return v * maxLength;
	}
	return v;
}

// The distance between two vectors
float Vector2::Distance(Vector2 from, Vector2 to)
{
	Vector2 vectorDistance = Vector2(to.x - from.x, to.y - from.y);
	return vectorDistance.Magnitude();
}

// The sum of the products of the corresponding entries of the vectors
// i=1, nΣaᶦbᶦ
float Vector2::Dot(Vector2 vectorA, Vector2 vectorB)
{
	return vectorA.x * vectorB.x + vectorA.y * vectorB.y;
}

// Use linear interpolation between two vectors
Vector2 Vector2::Lerp(Vector2 vectorA, Vector2 vectorB, float point)
{
	return vectorA + (vectorB - vectorA) * point;
}

// Returns a vector with the largest components
Vector2 Vector2::Max(Vector2 vectorA, Vector2 vectorB)
{
	float MaxX = vectorA.x;
	float MaxY = vectorA.y;

	if (vectorA.x < vectorB.x) MaxX = vectorB.x;
	if (vectorA.y < vectorB.y) MaxY = vectorB.y;
	
	return Vector2(MaxX, MaxY);
}

// Returns a vector with the smallest components
Vector2 Vector2::Min(Vector2 vectorA, Vector2 vectorB)
{
	float MinX = vectorA.x;
	float MinY = vectorA.y;

	if (vectorA.x > vectorB.x) MinX = vectorB.x;
	if (vectorA.y > vectorB.y) MinY = vectorB.y;

	return Vector2(MinX, MinY);
}


// █▀█ █▀█ █▀▀ █▀█ ▄▀█ ▀█▀ █▀█ █▀█ █▀
// █▄█ █▀▀ ██▄ █▀▄ █▀█ ░█░ █▄█ █▀▄ ▄█

// - Vector

// Adding to another vector
Vector2 Vector2::operator+(const Vector2& otherVector) { return { x + otherVector.x, y + otherVector.y }; }

// Subtracting to another vector
Vector2 Vector2::operator-(const Vector2& otherVector) { return { x - otherVector.x, y - otherVector.y }; }

// Multipling by another vector
Vector2 Vector2::operator*(const Vector2& otherVector) { return { x * otherVector.x, y * otherVector.y }; }

// Dividing by another vector
// NOTE: Is this dividing by the right way?
Vector2 Vector2::operator/(const Vector2& otherVector) { return { x / otherVector.x, y / otherVector.y }; }


// Adding to another vector
Vector2 Vector2::operator+=(const Vector2& otherVector)
{
	x += otherVector.x;
	y += otherVector.y;
	return *this;
}

// Subtracting to another vector
Vector2 Vector2::operator-=(const Vector2& otherVector)
{
	x -= otherVector.x;
	y -= otherVector.y;
	return *this;
}

// Multipling by another vector
Vector2 Vector2::operator*=(const Vector2& otherVector)
{
	x *= otherVector.x;
	y *= otherVector.y;
	return *this;
}

// Dividing by another vector
Vector2 Vector2::operator/=(const Vector2& otherVector)
{
	x /= otherVector.x;
	y /= otherVector.y;
	return *this;
}


// - Floats

// Adding to float
Vector2 Vector2::operator+(const float& amount) { return{ x + amount, y + amount }; }

// Subtracting by float
Vector2 Vector2::operator-(const float& amount) { return{ x - amount, y - amount }; }

// Multipling by float
Vector2 Vector2::operator*(const float& amount) { return{ x * amount, y * amount }; }

// Dividing by float
Vector2 Vector2::operator/(const float& amount) { return { x / amount, y / amount }; }

// Adding to float
Vector2 Vector2::operator+=(const float& amount)
{
	x += amount;
	y += amount;
	return *this;
}

// Subtracting by float
Vector2 Vector2::operator-=(const float& amount)
{
	x -= amount;
	y -= amount;
	return *this;
}

// Multipling by float
Vector2 Vector2::operator*=(const float& amount)
{
	x *= amount;
	y *= amount;
	return *this;
}

// Dividing by float
Vector2 Vector2::operator/=(const float& amount)
{
	x /= amount;
	y /= amount;
	return *this;
}


// - Ints

// Adding to int
Vector2 Vector2::operator+(const int& amount) { return{ x + amount, y + amount }; }

// Subtracting by int
Vector2 Vector2::operator-(const int& amount) { return{ x - amount, y - amount }; }

// Multipling by int
Vector2 Vector2::operator*(const int& amount) { return{ x * amount, y * amount }; }

// Dividing by int
Vector2 Vector2::operator/(const int& amount) { return { x / amount, y / amount }; }

// Adding to int
Vector2 Vector2::operator+=(const int& amount)
{
	x += amount;
	y += amount;
	return *this;
}

// Subtracting by int
Vector2 Vector2::operator-=(const int& amount)
{
	x -= amount;
	y -= amount;
	return *this;
}

// Multipling by int
Vector2 Vector2::operator*=(const int& amount)
{
	x *= amount;
	y *= amount;
	return *this;
}

// Dividing by int
Vector2 Vector2::operator/=(const int& amount)
{
	x /= amount;
	y /= amount;
	return *this;
}


// - Doubles

// Adding to double
Vector2 Vector2::operator+(const double& amount) { return{ x + (float)amount, y + (float)amount }; }

// Subtracting by double
Vector2 Vector2::operator-(const double& amount) { return{ x - (float)amount, y - (float)amount }; }

// Multipling by double
Vector2 Vector2::operator*(const double& amount) { return{ x * (float)amount, y * (float)amount }; }

// Dividing by double
Vector2 Vector2::operator/(const double& amount) { return { x / (float)amount, y / (float)amount }; }

// Adding to double
Vector2 Vector2::operator+=(const double& amount)
{
	x += amount;
	y += amount;
	return *this;
}

// Subtracting by double
Vector2 Vector2::operator-=(const double& amount)
{
	x -= amount;
	y -= amount;
	return *this;
}

// Multipling by double
Vector2 Vector2::operator*=(const double& amount)
{
	x *= amount;
	y *= amount;
	return *this;
}

// Dividing by double
Vector2 Vector2::operator/=(const double& amount)
{
	x /= amount;
	y /= amount;
	return *this;
}

