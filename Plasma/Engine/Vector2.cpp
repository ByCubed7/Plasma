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

// Single Float Constructor
Vector2::Vector2(const float coord)
{
	x = coord;
	y = coord;
}


// █▀▄▀█ █▀▀ ▀█▀ █░█ █▀█ █▀▄ █▀
// █░▀░█ ██▄ ░█░ █▀█ █▄█ █▄▀ ▄█

float Vector2::Magnitude()
{
	// a^2 + b^2 = c^2 
	return sqrt(x * x + y * y);
}

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

void Vector2::Negate()
{
	*this *= -1;
}

void Vector2::Set(float newX, float newY)
{
	x = newX;
	y = newY;
}

void Vector2::Round(int dp)
{
	x = round(x / dp) * dp;
	y = round(y / dp) * dp;
}

std::string Vector2::ToString()
{
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}


// █▀ ▀█▀ ▄▀█ ▀█▀ █ █▀▀   █▀▄▀█ █▀▀ ▀█▀ █░█ █▀█ █▀▄ █▀
// ▄█ ░█░ █▀█ ░█░ █ █▄▄   █░▀░█ ██▄ ░█░ █▀█ █▄█ █▄▀ ▄█



float Vector2::Angle(Vector2 from, Vector2 to)
{
	return acos((from.x * to.y + from.y * to.y) / (from.Magnitude() * to.Magnitude()));
}

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

float Vector2::Distance(Vector2 from, Vector2 to)
{
	Vector2 vectorDistance = Vector2(to.x - from.x, to.y - from.y);
	return vectorDistance.Magnitude();
}

float Vector2::Dot(Vector2 vectorA, Vector2 vectorB)
{
	return vectorA.x * vectorB.x + vectorA.y * vectorB.y;
}

Vector2 Vector2::Lerp(Vector2 vectorA, Vector2 vectorB, float point)
{
	return vectorA + (vectorB - vectorA) * point;
}

Vector2 Vector2::Max(Vector2 vectorA, Vector2 vectorB)
{
	float MaxX = vectorA.x;
	float MaxY = vectorA.y;

	if (vectorA.x < vectorB.x) MaxX = vectorB.x;
	if (vectorA.y < vectorB.y) MaxY = vectorB.y;
	
	return Vector2(MaxX, MaxY);
}

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


Vector2 Vector2::operator+(const Vector2& otherVector) { return { x + otherVector.x, y + otherVector.y }; } // Adding to another vector
Vector2 Vector2::operator-(const Vector2& otherVector) { return { x - otherVector.x, y - otherVector.y }; } // Subtracting to another vector
Vector2 Vector2::operator*(const Vector2& otherVector) { return { x * otherVector.x, y * otherVector.y }; } // Multipling by another vector
Vector2 Vector2::operator/(const Vector2& otherVector) { return { x / otherVector.x, y / otherVector.y }; } // Dividing by another vector
// ^ NOTE: Is this dividing by the right way?

// Adding to another vector
Vector2 Vector2::operator+=(const Vector2& otherVector)
{
	x += otherVector.x; y += otherVector.y;
	return *this;
}

// Subtracting to another vector
Vector2 Vector2::operator-=(const Vector2& otherVector)
{
	x -= otherVector.x; y -= otherVector.y;
	return *this;
}

// Multipling by another vector
Vector2 Vector2::operator*=(const Vector2& otherVector)
{
	x *= otherVector.x; y *= otherVector.y;
	return *this;
}

// Dividing by another vector
Vector2 Vector2::operator/=(const Vector2& otherVector)
{
	x /= otherVector.x; y /= otherVector.y;
	return *this;
}

//int Vector2::cmp(const Vector2& otherVector) const { return (x + y * 1000) - (otherVector.x + otherVector.y * 1000); }

//bool Vector2::operator==(const Vector2& otherVector) const { return cmp(otherVector) == 0; }
bool Vector2::operator==(const Vector2& otherVector) const { return x == otherVector.x && y == otherVector.y; }

//bool Vector2::operator< (const Vector2& otherVector) const { return cmp(otherVector) <  0; }
//bool Vector2::operator< (const Vector2& otherVector) const { return (x + y) < (otherVector.x + otherVector.y); }
//bool Vector2::operator< (const Vector2& otherVector) const { 
//	return sqrt(x * x + y * y) < sqrt(otherVector.x * otherVector.x + otherVector.y * otherVector.y);
//}
bool Vector2::operator< (const Vector2& otherVector) const
{
	if (x < otherVector.x) return true;
	if (x == otherVector.x)
	{
		if (y < otherVector.y) return true;
	}
	return false;
}

//bool Vector2::operator> (const Vector2& otherVector) const { return x + y > otherVector.x + otherVector.y; }
//bool Vector2::operator<=(const Vector2& otherVector) const { return x <= otherVector.x && y <= otherVector.y; }
//bool Vector2::operator>=(const Vector2& otherVector) const { return x >= otherVector.x && y >= otherVector.y; }

// - Floats

Vector2 Vector2::operator+(const float& amount) { return { x + amount, y + amount }; } // Adding to float
Vector2 Vector2::operator-(const float& amount) { return { x - amount, y - amount }; } // Subtracting by float
Vector2 Vector2::operator*(const float& amount) { return { x * amount, y * amount }; } // Multipling by float
Vector2 Vector2::operator/(const float& amount) { return { x / amount, y / amount }; } // Dividing by float

// Adding to float
Vector2 Vector2::operator+=(const float& amount)
{
	x += amount; y += amount;
	return *this;
}

// Subtracting by float
Vector2 Vector2::operator-=(const float& amount)
{	
	x -= amount; y -= amount;
	return *this;
}

// Multipling by float
Vector2 Vector2::operator*=(const float& amount)
{
	x *= amount; y *= amount;
	return *this;
}

// Dividing by float
Vector2 Vector2::operator/=(const float& amount)
{
	x /= amount; y /= amount;
	return *this;
}


// - Ints

Vector2 Vector2::operator+(const int& amount) { return { x + amount, y + amount }; } // Adding to int
Vector2 Vector2::operator-(const int& amount) { return { x - amount, y - amount }; } // Subtracting by int
Vector2 Vector2::operator*(const int& amount) { return { x * amount, y * amount }; } // Multipling by int
Vector2 Vector2::operator/(const int& amount) { return { x / amount, y / amount }; } // Dividing by int

// Adding to int
Vector2 Vector2::operator+=(const int& amount)
{
	x += amount; y += amount;
	return *this;
}

// Subtracting by int
Vector2 Vector2::operator-=(const int& amount)
{
	x -= amount; y -= amount;
	return *this;
}

// Multipling by int
Vector2 Vector2::operator*=(const int& amount)
{
	x *= amount; y *= amount;
	return *this;
}

// Dividing by int
Vector2 Vector2::operator/=(const int& amount)
{
	x /= amount; y /= amount;
	return *this;
}


// - Doubles

Vector2 Vector2::operator+(const double& amount) { return { x + (float)amount, y + (float)amount }; } // Adding to double
Vector2 Vector2::operator-(const double& amount) { return { x - (float)amount, y - (float)amount }; } // Subtracting by double
Vector2 Vector2::operator*(const double& amount) { return { x * (float)amount, y * (float)amount }; } // Multipling by double
Vector2 Vector2::operator/(const double& amount) { return { x / (float)amount, y / (float)amount }; } // Dividing by double

// Adding to double
Vector2 Vector2::operator+=(const double& amount)
{
	x += amount; y += amount;
	return *this;
}

// Subtracting by double
Vector2 Vector2::operator-=(const double& amount)
{
	x -= amount; y -= amount;
	return *this;
}

// Multipling by double
Vector2 Vector2::operator*=(const double& amount)
{
	x *= amount; y *= amount;
	return *this;
}

// Dividing by double
Vector2 Vector2::operator/=(const double& amount)
{
	x /= amount; y /= amount;
	return *this;
}

