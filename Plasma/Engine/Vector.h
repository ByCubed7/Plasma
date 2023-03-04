#pragma once

#include <stdint.h>
#include <array>
#include <algorithm>
#include <iostream>
#include <string>
#include <math.h>

// https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl

/* https://stackoverflow.com/questions/456713/why-do-i-get-unresolved-external-symbol-errors-when-using-templates
* Templated classes and functions are not instantiated until they are used, typically in a separate .cpp file (e.g. the program source).
* When the template is used, the compiler needs the full code for that function to be able to build the correct function with the appropriate type.
* However, in this case the code for that function is detailed in the template's source file and hence unavailable.
* - dlanod
*/

// One solution would to be to also include the .cpp file. However, this may send the wrong message.
// TEST: Create a "VectorImple.h" file which includes both .h .cpp files and see if we get an Unresolved External exception


/// <summary>
/// <para>"Hey."</para> 
/// <para>"I'm applying for a new villain loan going by the name of vector."</para> 
/// <para>"It's a mathematical term, a quantity represented by an arrow with both direction and magnitude!"</para> 
/// <para>"Vector. That's me, because I'm committing crimes with both direction and magnitude!"</para> 
/// <para>"Oh yeah!"</para>
/// </summary>
/// <typeparam name="T">The vectors type.</typeparam>
/// <typeparam name="N">The size of the vector.</typeparam>
template<class T, size_t N>
class Vector
{
public:

    // - Contructors
    Vector() : _contents{ 0 }
    {
        //_contents = std::array<T, N>({ 0 });
        for (int i = 0; i < N; i++)
            _contents[i] = 0;
    }

    Vector(T value) : _contents{ value }
    {
        for (int i = 0; i < N; i++)
            _contents[i] = value;
    }

    Vector(std::initializer_list<T> value) : _contents{ 0 }
    {
        const T* it = value.begin();
        const T* const end = value.end();
        for (int i = 0; it != end; ++it, ++i)
            _contents[i] = *it;
        //std::copy(std::begin(value), std::end(value), std::begin(_contents));
    }

    // Copy Constructor
    Vector(const Vector& value) : _contents{ 0 }
    {
        for (int i = 0; i < N; i++)
            _contents[i] = value._contents[i];
    }


    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // - Gets and Sets

    // https://stackoverflow.com/questions/856542/elegant-solution-to-duplicate-const-and-non-const-getters
    constexpr T Get(int index) { return _contents[index]; }
    //constexpr const T Get(int index) const { return _contents[index]; }

    //void Set(int index, T value) { _contents[index] = value; }


    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // - Functionallities

    /// <summary>Gets the size of the Vector.</summary>
    /// <returns>The size of the Vector.</returns>
    constexpr size_t Size() { return N; }

    void Invert() {
        for (int i = 0; i < N; i++) _contents[i] = -_contents[i];
    }
    //void Invert(int index) { return Set(index, -Get(index)); }

    T Magnitude() {
        return std::sqrt(MagnitudeSquared());
    }

    T MagnitudeSquared() {
        T total = 0;
        // a^2 + b^2 + ... = magnitude^2 
        for (int i = 0; i < N; i++) total += (_contents[i] * _contents[i]);

        return total;
    }

    Vector<T, N> Normalize()
    {
        T length = Magnitude();

        Vector<T, N> newVector = Vector<T, N>();
        if (length == 0) return newVector;

        for (int i = 0; i < N; i++)
            newVector._contents[i] = _contents[i] / length;

        return newVector;
    }

    Vector<T, N> Round(T dp = 1)
    {
        Vector<T, N> newVector = Vector<T, N>();
        for (int i = 0; i < N; i++)
            newVector._contents[i] = round(_contents[i] / dp) * dp;
        return newVector;
    }


    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // - Static methods

    // Random
    static Vector<T, N> Random(Vector<int, N> bounds) {
        Vector<T, N> randomVector = Vector<T, N>();

        for (int i = 0; i < N; i++)
            randomVector._contents[i] = (T)(rand() % bounds.Get(i));

        return randomVector;
    }

    static T Distance(Vector<T, N> vectorFrom, Vector<T, N> vectorTo)
    {
        return (vectorTo - vectorFrom).Magnitude();
    }

    static Vector<T, N> Lerp(Vector<T, N> vectorA, Vector<T, N> vectorB, float point)
    {
        return vectorA + (vectorB - vectorA) * point;
    }

    static Vector<T, N> Max(Vector<T, N> vectorA, Vector<T, N> vectorB)
    {
        Vector<T, N> maxVector = Vector<T, N>(vectorA);

        for (int i = 0; i < N; i++)
        {
            if (vectorA._contents[i] < vectorB._contents[i])
                maxVector._contents[i] = vectorB._contents[i];
        }

        return maxVector;
    }

    static Vector<T, N> Min(Vector<T, N> vectorA, Vector<T, N> vectorB)
    {
        Vector<T, N> minVector = Vector<T, N>(vectorA);

        for (int i = 0; i < N; i++)
        {
            if (vectorA._contents[i] > vectorB._contents[i])
                minVector._contents[i] = vectorB._contents[i];
        }

        return minVector;
    }

    static T Dot(Vector<T, N> vectorA, Vector<T, N> vectorB)
    {
        T total = 0;
        for (int i = 0; i < N; i++) total += vectorA._contents[i] * vectorB._contents[i];
        return total;
    }


    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // - Resizing and Retyping

    /// <summary>Resizes the vector.</summary>
    /// <param name="filler">- the default value to fill in empty elements with.</param>
    /// <typeparam name="newN">The new size to expand the vector to.</typeparam>
    /// <returns>The resized vector.</returns>
    template<size_t newN>
    constexpr Vector<T, newN> Resize(T filler = 0) {
        Vector<T, newN> newVector = Vector<T, newN>();
        for (int i = 0; i < newN; i++)
            newVector._contents[i] = _contents.size() > i ? _contents[i] : filler;

        return newVector;
    }

    /// <summary>Casts the vectors value to another type.</summary>
    /// <typeparam name="newT">The new type to assign the values to.</typeparam>
    /// <returns>The casted vector.</returns>
    template<class newT>
    constexpr Vector<newT, N> Cast() {
        Vector<newT, N> newVector = Vector<newT, N>();
        for (int i = 0; i < N; i++)
            newVector._contents[i] = (newT)_contents[i];

        return newVector;
    }

    /// <summary>No idea why you would use this, appends one vector onto the other.</summary>
    /// <param name="first">- the first vector.</param>
    /// <param name="second">- the second vector.</param>
    /// <returns>The appended vector.</returns>
    template<size_t A, size_t B>
    static Vector<T, A + B> Append(Vector<T, A> first, Vector<T, B> second) {
        Vector<T, A + B> newVector = Vector<T, A + B>();

        for (int i = 0; i < A; i++)
            newVector._contents[i] = first._contents[i];

        for (int i = 0; i < B; i++)
            newVector._contents[A + i] = second._contents[i];

        return newVector;
    }


    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // - Assignment opperators

    // Vector
    Vector<T, N>& operator=(const Vector<T, N>& other)
    {
        for (int i = 0; i < N; i++) _contents[i] = other._contents[i];
        return *this;
    }

    // Value
    Vector<T, N>& operator=(const T& other)
    {
        for (int i = 0; i < N; i++) _contents[i] = other;
        return *this;
    }


    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // - Increment & decrement opperators

    // Prefix increment
    Vector<T, N>& operator++()
    {
        for (T& value : _contents) value++; // Increment
        return *this; // return by reference
    }

    // Postfix increment
    Vector<T, N> operator++(int)
    {
        Vector<T, N> old = *this; // copy old value
        operator++();  // prefix
        return old;    // return old value
    }

    // Prefix decrement
    Vector<T, N>& operator--()
    {
        for (T& value : _contents) value--; // Deincrement
        return *this; // return by reference
    }

    // Postfix decrement
    Vector<T, N> operator--(int)
    {
        Vector<T, N> old = *this; // copy old value
        operator--();  // prefix
        return old;    // return old value
    }


    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // - Equality

    bool operator==(const Vector<T, N>& other) const
    {
        for (int i = 0; i < N; i++)
            if (_contents[i] != other._contents[i])
                return false;
        return true;
    }

    bool operator!=(const Vector<T, N>& other) const
    {
        return !(operator==(other));
    }

    bool operator<(const Vector<T, N>& other) const
    {
        for (int i = 0; i < N; i++)
        {
            if (_contents[i] == other._contents[i]) continue;
            return _contents[i] < other._contents[i];
        }
        return false;
    }

    bool operator>(const Vector<T, N>& other) const
    {
        for (int i = 0; i < N; i++)
        {
            if (_contents[i] == other._contents[i]) continue;
            return _contents[i] > other._contents[i];
        }
        return false;
    }


    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // - Adding

    // vector
    Vector<T, N> operator+(const Vector<T, N>& other)
    {
        Vector<T, N> newVector = Vector<T, N>();
        for (int i = 0; i < N; i++) newVector._contents[i] = _contents[i] + other._contents[i];
        return newVector;
    }

    Vector<T, N>& operator+=(const Vector<T, N>& other)
    {
        for (int i = 0; i < N; i++) _contents[i] += other._contents[i];
        return *this;
    }

    // T
    Vector<T, N> operator+(const T& other)
    {
        Vector<T, N> newVector = Vector<T, N>();
        for (int i = 0; i < N; i++) newVector._contents[i] = _contents[i] + other;
        return newVector;
    }

    Vector<T, N>& operator+=(const T& other)
    {
        for (int i = 0; i < N; i++) _contents[i] += other;
        return *this;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // - Subtracting

    // vector
    Vector<T, N> operator-(const Vector<T, N>& other)
    {
        Vector<T, N> newVector = Vector<T, N>();
        for (int i = 0; i < N; i++) newVector._contents[i] = _contents[i] - other._contents[i];
        return newVector;
    }

    Vector<T, N>& operator-=(const Vector<T, N>& other)
    {
        for (int i = 0; i < N; i++) _contents[i] -= other._contents[i];
        return *this;
    }

    // T
    Vector<T, N> operator-(const T& other)
    {
        Vector<T, N> newVector = Vector<T, N>();
        for (int i = 0; i < N; i++) newVector._contents[i] = _contents[i] - other;
        return newVector;
    }

    Vector<T, N>& operator-=(const T& other)
    {
        for (int i = 0; i < N; i++) _contents[i] -= other;
        return *this;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // - Multiplying

    // vector
    Vector<T, N> operator*(const Vector<T, N>& other)
    {
        Vector<T, N> newVector = Vector<T, N>();
        for (int i = 0; i < N; i++) newVector._contents[i] = _contents[i] * other._contents[i];
        return newVector;
    }

    Vector<T, N>& operator*=(const Vector<T, N>& other)
    {
        for (int i = 0; i < N; i++) _contents[i] *= other._contents[i];
        return *this;
    }

    // T
    Vector<T, N> operator*(const T& other)
    {
        Vector<T, N> newVector = Vector<T, N>();
        for (int i = 0; i < N; i++) newVector._contents[i] = _contents[i] * other;
        return newVector;
    }

    Vector<T, N>& operator*=(const T& other)
    {
        for (int i = 0; i < N; i++) _contents[i] *= other;
        return *this;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // - Divide

    // vector
    Vector<T, N> operator/(const Vector<T, N>& other)
    {
        Vector<T, N> newVector = Vector<T, N>();
        for (int i = 0; i < N; i++) newVector._contents[i] = _contents[i] / other._contents[i];
        return newVector;
    }

    Vector<T, N>& operator/=(const Vector<T, N>& other)
    {
        for (int i = 0; i < N; i++) _contents[i] /= other._contents[i];
        return *this;
    }

    // T
    Vector<T, N> operator/(const T& other)
    {
        Vector<T, N> newVector = Vector<T, N>();
        for (int i = 0; i < N; i++) newVector._contents[i] = _contents[i] / other;
        return newVector;
    }

    Vector<T, N>& operator/=(const T& other)
    {
        for (int i = 0; i < N; i++) _contents[i] /= other;
        return *this;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // - Negative operator

    Vector<T, N> operator-()
    {
        Vector<T, N> newVector = Vector<T, N>();
        for (int i = 0; i < N; i++) newVector._contents[i] = -_contents[i];
        return newVector;
    }


    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // - Casting

    // To string
    operator std::string() {
        std::string string;

        for (int i = 0; i < N; i++) {
            string += std::to_string(_contents[i]);
            if (i != N - 1) string += ", ";
        }

        return string;
    }

    friend std::ostream& operator<< (std::ostream& os, const Vector<T, N>& other)
    {
        for (int i = 0; i < N; i++) {
            os << std::to_string(other._contents[i]);
            if (i != N - 1) os << ", ";
        }
        return os;
    }

    /*std::string operator<< (const std::string& other) const
    {
        return other + operator std::string();
    }*/

protected:
    std::array<T, N> _contents;
};


// All of this, just to use vector.x  :`)
class Vector3 : public Vector<float, 3Ui64>
{
public:
    using Vector<float, 3Ui64>::Vector;

    Vector3()
        : Vector<float, 3Ui64>() {}

    Vector3(const Vector& value)
        : Vector<float, 3Ui64>(value) {}

    Vector3& operator=(Vector3 other) {
        Vector<float, 3Ui64>::operator=(other);
        return *this;
    }

    float& x = _contents[0];
    float& y = _contents[1];
    float& z = _contents[2];
};


class Vector2 : public Vector<float, 2Ui64>
{
public:
    using Vector<float, 2Ui64>::Vector;

    Vector2()
        : Vector<float, 2Ui64>() {}

    Vector2(const Vector& value)
        : Vector<float, 2Ui64>(value) {}

    Vector2& operator=(Vector2 other) {
        Vector<float, 2Ui64>::operator=(other);
        return *this;
    }

    float& x = _contents[0];
    float& y = _contents[1];
};


class Vector2Int : public Vector<int, 2Ui64>
{
public:
    using Vector<int, 2Ui64>::Vector;

    Vector2Int()
        : Vector<int, 2Ui64>() {}

    Vector2Int(const Vector& value)
        : Vector<int, 2Ui64>(value) {}

    Vector2Int& operator=(Vector2Int other) {
        Vector<int, 2Ui64>::operator=(other);
        return *this;
    }

    int& x = _contents[0];
    int& y = _contents[1];
};


class Vector2UInt : public Vector<unsigned int, 2Ui64>
{
public:
    using Vector<unsigned int, 2Ui64>::Vector;

    Vector2UInt()
        : Vector<unsigned int, 2Ui64>() {}

    Vector2UInt(const Vector& value)
        : Vector<unsigned int, 2Ui64>(value) {}

    Vector2UInt& operator=(Vector2UInt other) {
        Vector<unsigned int, 2Ui64>::operator=(other);
        return *this;
    }

    unsigned int& x = _contents[0];
    unsigned int& y = _contents[1];
};


class Color3 : public Vector<unsigned __int8, 3Ui64>
{
public:
    using Vector<unsigned __int8, 3Ui64>::Vector;

    Color3()
        : Vector<unsigned __int8, 3Ui64>() {}

    Color3(const Vector& value)
        : Vector<unsigned __int8, 3Ui64>(value) {}

    Color3& operator=(Color3 other) {
        Vector<unsigned __int8, 3Ui64>::operator=(other);
        return *this;
    }

    unsigned __int8& x = _contents[0];
    unsigned __int8& y = _contents[1];
    unsigned __int8& z = _contents[2];

    unsigned __int8& r = _contents[0];
    unsigned __int8& g = _contents[1];
    unsigned __int8& b = _contents[2];
};


class Colour4 : public Vector<unsigned __int8, 4Ui64>
{
public:
    using Vector<unsigned __int8, 4Ui64>::Vector;

    Colour4()
        : Vector<unsigned __int8, 4Ui64>() {}

    Colour4(const Vector& value)
        : Vector<unsigned __int8, 4Ui64>(value) {}

    Colour4& operator=(Colour4 other) {
        Vector<unsigned __int8, 4Ui64>::operator=(other);
        return *this;
    }

    unsigned __int8& x = _contents[0];
    unsigned __int8& y = _contents[1];
    unsigned __int8& z = _contents[2];
    unsigned __int8& w = _contents[3];

    unsigned __int8& r = _contents[0];
    unsigned __int8& g = _contents[1];
    unsigned __int8& b = _contents[2];
    unsigned __int8& a = _contents[3];
};