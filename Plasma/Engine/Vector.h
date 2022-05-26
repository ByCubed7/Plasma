#pragma once

#include "Object.h"
//#include "Vector2 OLD.h"

#include <stdint.h>
#include <array>
#include <algorithm>
#include <iostream>
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

//namespace Engine:: {

template<class T, int N>
class Vector : public Object
{
public:

    // - Contructors
    Vector() : Object("Vector"), _contents{ 0 },
        x(_contents[0]), y(_contents[1]), z(_contents[2]), w(_contents[3])
    {
        _contents = std::array<T, N>({ 0 });
    }

    Vector(T value) : Object("Vector"), _contents{ value },
        x(_contents[0]), y(_contents[1]), z(_contents[2]), w(_contents[3])
    {
        for (int i = 0; i < N; i++)
            _contents[i] = value;
    }

    Vector(std::initializer_list<T> value) : Object("Vector"), _contents{ 0 },
        x(_contents[0]), y(_contents[1]), z(_contents[2]), w(_contents[3])
    {
        const T* it = value.begin();
        const T* const end = value.end();

        for (int i = 0; it != end; ++it, ++i) {
            _contents[i] = *it;
        }
        //std::copy(std::begin(value), std::end(value), std::begin(_contents));
    }

    // Copy Constructor
    Vector(const Vector<T, N>& value) : Object("Vector"), _contents{ 0 },
        x(_contents[0]), y(_contents[1]), z(_contents[2]), w(_contents[3])
    {
        for (int i = 0; i < N; i++)
            _contents[i] = value._contents[i];
    }


    // ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
    // - Functionallities

    // Gets the size of the Vector
    constexpr size_t Size() { return N; }

    // Verbose functions
    constexpr T Get(int index) { return _contents[index]; }
    constexpr T X() { return Get(0); }
    constexpr T Y() { return Get(1); }
    constexpr T Z() { return Get(2); }
    constexpr T W() { return Get(3); }

    // Const Verbose functions
    constexpr const T Get(int index) const { return _contents[index]; }
    constexpr const T X() const { return Get(0); }
    constexpr const T Y() const { return Get(1); }
    constexpr const T Z() const { return Get(2); }
    constexpr const T W() const { return Get(3); }

    T Magnitude() {
        T total = 0;
        // a^2 + b^2 + ... = magnitude^2 
        for (int i = 0; i < N; i++) total += (_contents[i] * _contents[i]);

        return sqrt(total);
    }

    // https://stackoverflow.com/questions/856542/elegant-solution-to-duplicate-const-and-non-const-getters
    //const T& get(int index) const
    //{
    //    //non-trivial work
    //    return _contents[index];
    //}

    //int& get(int index)
    //{
    //    return const_cast<T&>(const_cast<const Vector*>(this)->get(index));
    //}

    void Set(int index, T value) { _contents[index] = value; }
    void SetX(T value) { Set(0, value); }
    void SetY(T value) { Set(1, value); }
    void SetZ(T value) { Set(2, value); }
    void SetW(T value) { Set(3, value); }

    void Invert() {
        for (int i = 0; i < N; i++) _contents[i] = -_contents[i];
    }
    //void Invert(int index) { return Set(index, -Get(index)); }

    void Normalize()
    {
        T length = Magnitude();

        if (length == 0) return;
        //    for (int i = 0; i < N; i++)
        //        _contents[i] = 0;
        //    return;

        for (int i = 0; i < N; i++)
            _contents[i] = _contents[i] / length;
    }

    void Round(int dp = 1)
    {
        for (int i = 0; i < N; i++)
            _contents[i] = round(_contents[i] / dp) * dp;
    }

    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
    // Static methods

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

    static T Dot(Vector<T, N> vectorA, Vector<T, N> vectorB, float point)
    {
        T total = 0;
        for (int i = 0; i < N; i++) total += vectorA._contents[i] + vectorB._contents[i];
        return total;
    }


    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
    // # Resizing and Retyping

    template<int newN>
    constexpr Vector<T, newN> Resize(int filler = 0) {
        Vector<T, newN> newVector = Vector<T, newN>();
        for (int i = 0; i < newN; i++) {
            newVector._contents[i] = _contents.size() > i ? _contents[i] : filler;
        }
        return newVector;
    }

    template<class newT>
    constexpr Vector<newT, N> Cast() {
        Vector<newT, N> newVector = Vector<newT, N>();
        for (int i = 0; i < N; i++) {
            newVector._contents[i] = (newT)_contents[i];
        }
        return newVector;
    }

    template<int A, int B>
    static Vector<T, A + B> Append(Vector<T, A> first, Vector<T, B> second) {
        Vector<T, A + B> newVector = Vector<T, A + B>();

        for (int i = 0; i < A; i++)
            newVector._contents[i] = first._contents[i];

        for (int i = 0; i < B; i++)
            newVector._contents[A + i] = second._contents[i];

        return newVector;
    }

    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
    // # Assignments and Opperators

    // Equals
    /*Vector<T, N>& operator =(const Vector<T, N>& other)
    {
        for (int i = 0; i < N; i++) _contents[i] = other._contents[i];
        return *this;
    }//*/
    //*
    Vector<T, N> operator=(const Vector<T, N>& other)
    {
        Vector<T, N> newVector = Vector<T, N>();
        for (int i = 0; i < N; i++) _contents[i] = other._contents[i];
        return newVector;
    }//*/


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



    bool operator==(const Vector<T, N>& other) const
    {
        for (int i = 0; i < N; i++) if (_contents[i] != other._contents[i]) return false;
        return true;
    }
    bool operator!=(const Vector<T, N>& other) const
    {
        return !(operator==(other));
    }

    bool operator< (const Vector<T, N>& other) const
    {
        for (int i = 0; i < N; i++)
        {
            if (_contents[i] == other._contents[i]) continue;
            if (_contents[i] < other._contents[i]) return true;
            return false;
        }
    }
    bool operator> (const Vector<T, N>& other) const
    {
        for (int i = 0; i < N; i++)
        {
            if (_contents[i] == other._contents[i]) continue;
            if (_contents[i] > other._contents[i]) return true;
            return false;
        }
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

    // int
    Vector<T, N> operator+(const int& other)
    {
        Vector<T, N> newVector = Vector<T, N>();
        for (int i = 0; i < N; i++) newVector._contents[i] = _contents[i] + other;
        return newVector;
    }

    Vector<T, N>& operator+=(const int& other)
    {
        for (int i = 0; i < N; i++) _contents[i] += other;
        return *this;
    }

    // float
    Vector<T, N> operator+(const float& other)
    {
        Vector<T, N> newVector = Vector<T, N>();
        for (int i = 0; i < N; i++) newVector._contents[i] = _contents[i] + other;
        return newVector;
    }

    Vector<T, N>& operator+=(const float& other)
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

    // int
    Vector<T, N> operator-(const int& other)
    {
        Vector<T, N> newVector = Vector<T, N>();
        for (int i = 0; i < N; i++) newVector._contents[i] = _contents[i] - other;
        return newVector;
    }

    Vector<T, N>& operator-=(const int& other)
    {
        for (int i = 0; i < N; i++) _contents[i] -= other;
        return *this;
    }

    // float
    Vector<T, N> operator-(const float& other)
    {
        Vector<T, N> newVector = Vector<T, N>();
        for (int i = 0; i < N; i++) newVector._contents[i] = _contents[i] - other;
        return newVector;
    }

    Vector<T, N>& operator-=(const float& other)
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

    // int
    Vector<T, N> operator*(const int& other)
    {
        Vector<T, N> newVector = Vector<T, N>();
        for (int i = 0; i < N; i++) newVector._contents[i] = _contents[i] * other;
        return newVector;
    }

    Vector<T, N>& operator*=(const int& other)
    {
        for (int i = 0; i < N; i++) _contents[i] *= other;
        return *this;
    }

    // float
    Vector<T, N> operator*(const float& other)
    {
        Vector<T, N> newVector = Vector<T, N>();
        for (int i = 0; i < N; i++) newVector._contents[i] = _contents[i] * other;
        return newVector;
    }

    Vector<T, N>& operator*=(const float& other)
    {
        for (int i = 0; i < N; i++) _contents[i] *= other;
        return *this;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // - Divide

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

    // int
    Vector<T, N> operator/(const int& other)
    {
        Vector<T, N> newVector = Vector<T, N>();
        for (int i = 0; i < N; i++) newVector._contents[i] = _contents[i] / other;
        return newVector;
    }

    Vector<T, N>& operator/=(const int& other)
    {
        for (int i = 0; i < N; i++) _contents[i] /= other;
        return *this;
    }

    // float
    Vector<T, N> operator/(const float& other)
    {
        Vector<T, N> newVector = Vector<T, N>();
        for (int i = 0; i < N; i++) newVector._contents[i] = _contents[i] / other;
        return newVector;
    }

    Vector<T, N>& operator/=(const float& other)
    {
        for (int i = 0; i < N; i++) _contents[i] /= other;
        return *this;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -



    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 

    // Casting

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


    // *Should* be private, but it's much easier to reference this when it's not-
    std::array<T, N> _contents;
    T& x; T& y; T& z; T& w;
};


// Some Cool™ sugar syntax typedefs

typedef class Vector<int, 2> Vector2Int;
typedef class Vector<float, 2> Vector2Float;
typedef class Vector<float, 2> Vector2;

typedef class Vector<unsigned __int8, 3> RGB;
typedef class Vector<unsigned __int8, 4> RGBA;

//}

