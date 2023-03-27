#pragma once

#ifdef min
#undef min
#undef max
#endif

#include <stdint.h>
#include <array>
#include <iostream>
#include <string>
#include <math.h>
//#include <algorithm>

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
/// <typeparam name="T">The vectors return type.</typeparam>
/// <typeparam name="R">The vectors type.</typeparam>
/// <typeparam name="N">The size of the vector.</typeparam>
template<class Type, class Value, size_t N> 
class Vector
{
public:
    // Default Contructors
    Vector() : _contents{}
    {
        static_assert(std::is_base_of<Vector, Type>::value, "Type parameter of this class must derive from Vector");

        for (int i = 0; i < N; i++)
            _contents[i] = 0;
    }

    // Value Constructor
    Vector(const Value& value) : _contents{}
    {
        for (int i = 0; i < N; i++)
            _contents[i] = value;
    }

    // Type Constructor
    Vector(const Type& value) : _contents{ value._contents } {}

    // Initializer List Constructor
    Vector(const std::initializer_list<Value>& value) : _contents{ 0 }
    {
        const Value* it = value.begin();
        const Value* const end = value.end();
        for (int i = 0; it != end; ++it, ++i)
            _contents[i] = *it;
        //std::copy(std::begin(value), std::end(value), std::begin(_contents));
    }


    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // - Gets and Sets

    // https://stackoverflow.com/questions/856542/elegant-solution-to-duplicate-const-and-non-const-getters
    //constexpr T Get(int index) { return _contents[index]; }
    //constexpr const T Get(int index) const { return _contents[index]; }

    //void Set(int index, T value) { _contents[index] = value; }


    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // - Functionallities

    /// <summary>Gets the size of the Vector.</summary>
    /// <returns>The size of the Vector.</returns>
    constexpr size_t size() const { return N; }


    void invert() {
        for (int i = 0; i < N; i++) _contents[i] = -_contents[i];
    }
    //void Invert(int index) { return Set(index, -Get(index)); }

    Value magnitude() const {
        return std::sqrt(magnitudeSquared());
    }

    Value magnitudeSquared() const {
        Value total = 0;
        // a^2 + b^2 + ... = magnitude^2 
        for (int i = 0; i < N; i++) 
            total += (_contents[i] * _contents[i]);

        return total;
    }

    Type normalize() const {
        Value length = magnitude();

        Type newVector = Type();
        if (length == 0) return newVector;

        for (int i = 0; i < N; i++)
            newVector._contents[i] = _contents[i] / length;

        return newVector;
    }
    
    Type round(Value dp = 1) const {
        Type newVector = Type();
        for (int i = 0; i < N; i++)
            newVector._contents[i] = std::round(_contents[i] / dp) * dp;
        return newVector;
    }

    Type project(const Type& other) const {
        float magn = other.magnitudeSquared();
        if (magn == 0)
            return 0;

        return other * (dot(other) / magn);
    }

    Type reject(const Type& other) const {
        return *this - project(other);
    }


    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // - Static methods

    // Random
    static Type random(const Vector& bounds) {
        Type randomVector = Type();

        for (int i = 0; i < N; i++) {
            randomVector._contents[i] = (Value)(rand() % (int)bounds._contents[i]);
        }

        return randomVector;
    }

    static Value distance(const Type& vectorFrom, const Type& vectorTo)
    {
        return (vectorTo - vectorFrom).magnitude();
    }

    static Type lerp(const Type& vectorA, const Type& vectorB, float point)
    {
        return vectorA + (vectorB - vectorA) * point;
    }

    static Type max(const Type& vectorA, const Type& vectorB)
    {
        Type maxVector = Type(vectorA);

        for (int i = 0; i < N; i++)
        {
            if (vectorA._contents[i] < vectorB._contents[i])
                maxVector._contents[i] = vectorB._contents[i];
        }

        return maxVector;
    }

    static Type min(const Type& vectorA, const Type& vectorB)
    {
        Type minVector = Type(vectorA);

        for (int i = 0; i < N; i++)
        {
            if (vectorA._contents[i] > vectorB._contents[i])
                minVector._contents[i] = vectorB._contents[i];
        }

        return minVector;
    }


    static Value dot(const Type& vectorA, const Type& vectorB)
    {
        return vectorA.dot(vectorB);
    }

    Value dot(const Type& other) const
    {
        Value total = 0;
        for (int i = 0; i < N; i++) total += _contents[i] * other._contents[i];
        return total;
    }

    Value dot() const
    {
        Value total = 0;
        for (int i = 0; i < N; i++) total += _contents[i] * _contents[i];
        return total;
    }


    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // - Resizing and Retyping

    /// <summary>Resizes the vector.</summary>
    /// <param name="filler">- the default value to fill in empty elements with.</param>
    /// <typeparam name="newN">The new size to expand the vector to.</typeparam>
    /// <returns>The resized vector.</returns>
    template<size_t newN>
    constexpr Vector<Type, Value, newN> Resize(Value filler = 0) {
        Vector<Type, Value, newN> newVector = Vector<Type, Value, newN>();
        for (int i = 0; i < newN; i++)
            newVector._contents[i] = _contents.size() > i ? _contents[i] : filler;
        
        return newVector;
    }

    /// <summary>Casts the vectors value to another type.</summary>
    /// <typeparam name="newT">The new type to assign the values to.</typeparam>
    /// <returns>The casted vector.</returns>
    template<class newType>
    newType Cast() {
        newType newVector = {};
        for (int i = 0; i < N; i++)
            newVector._contents[i] = _contents[i];
        
        return newVector;
    }


    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // - Assignment opperators

    // Vector
    Vector<Type, Value, N>& operator=(const Type& other)
    {
        for (int i = 0; i < N; i++) _contents[i] = other._contents[i];
        return *this;
    }

    // Value
    Vector<Type, Value, N>& operator=(const Value& other)
    {
        for (int i = 0; i < N; i++) _contents[i] = other;
        return *this;
    }


    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // - Negation opperator

    Type operator-() const {
        Type newVector = Type();
        for (int i = 0; i < N; i++) 
            newVector._contents[i] = -_contents[i];
        return newVector;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // - Increment & decrement opperators

    // Prefix increment
    Vector<Type, Value, N>& operator++()
    {
        for (Value& value : _contents) value++; // Increment
        return *this; // return by reference
    }

    // Postfix increment
    Vector<Type, Value, N> operator++(int)
    {
        auto old = *this; // copy old value
        operator++();  // prefix
        return old;    // return old value
    }

    // Prefix decrement
    Vector<Type, Value, N>& operator--()
    {
        for (Value& value : _contents) value--; // Deincrement
        return *this; // return by reference
    }

    // Postfix decrement
    Vector<Type, Value, N> operator--(int)
    {
        auto old = *this; // copy old value
        operator--();  // prefix
        return old;    // return old value
    }


    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // - Equality

    bool operator==(const Type& other) const
    {
        for (int i = 0; i < N; i++) 
            if (_contents[i] != other._contents[i]) 
                return false;
        return true;
    }

    bool operator!=(const Type& other) const
    {
        return !(operator==(other));
    }

    bool operator<(const Type& other) const
    {
        for (int i = 0; i < N; i++)
        {
            if (_contents[i] == other._contents[i]) continue;
            return _contents[i] < other._contents[i];
        }
        return false;
    }

    bool operator>(const Type& other) const
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
    Type operator+(const Type& other)
    {
        Type newVector = Type();
        for (int i = 0; i < N; i++) newVector._contents[i] = _contents[i] + other._contents[i];
        return newVector;
    }

    //friend Type operator+(const Type& lhs, const Type& rhs) {
    //    Type result = Type();
    //    for (int i = 0; i < N; ++i) {
    //        result._contents[i] = lhs._contents[i] + rhs._contents[i];
    //    }
    //    return result;
    //}

    Vector<Type, Value, N>& operator+=(const Type& other)
    {
        for (int i = 0; i < N; i++) _contents[i] += other._contents[i];
        return *this;
    }

    // T
    Type operator+(const Value& other)
    {
        Type newVector = Type();
        for (int i = 0; i < N; i++) newVector._contents[i] = _contents[i] + other;
        return newVector;
    }

    Vector<Type, Value, N>& operator+=(const Value& other)
    {
        for (int i = 0; i < N; i++) _contents[i] += other;
        return *this;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // - Subtracting

    // vector
    Type operator-(const Type& other)
    {
        Type newVector = Type();
        for (int i = 0; i < N; i++) 
            newVector._contents[i] = _contents[i] - other._contents[i];
        return newVector;
    }

    /*friend Type operator-(const Type& lhs, const Type& rhs) {
        Type result = Type();
        for (int i = 0; i < lhs.size(); ++i)
            result._contents[i] = lhs._contents[i] - rhs._contents[i];
        return result;
    }*/

    Vector<Type, Value, N>& operator-=(const Type& other)
    {
        for (int i = 0; i < N; i++) _contents[i] -= other._contents[i];
        return *this;
    }

    // T
    Type operator-(const Value& other)
    {
        Type newVector = Type();
        for (int i = 0; i < N; i++) newVector._contents[i] = _contents[i] - other;
        return newVector;
    }

    Vector<Type, Value, N>& operator-=(const Value& other)
    {
        for (int i = 0; i < N; i++) _contents[i] -= other;
        return *this;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // - Multiplying

    // vector
    Type operator*(const Type& other)
    {
        Type newVector = Type();
        for (int i = 0; i < N; i++) newVector._contents[i] = _contents[i] * other._contents[i];
        return newVector;
    }

    Vector<Type, Value, N>& operator*=(const Type& other)
    {
        for (int i = 0; i < N; i++) _contents[i] *= other._contents[i];
        return *this;
    }

    // T
    Type operator*(const Value& other)
    {
        Type newVector = Type();
        for (int i = 0; i < N; i++) newVector._contents[i] = _contents[i] * other;
        return newVector;
    }

    Vector<Type, Value, N>& operator*=(const Value& other)
    {
        for (int i = 0; i < N; i++) _contents[i] *= other;
        return *this;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // - Divide

    // vector
    Type operator/(const Type& other)
    {
        Type newVector = Type();
        for (int i = 0; i < N; i++) newVector._contents[i] = _contents[i] / other._contents[i];
        return newVector;
    }

    Vector<Type, Value, N>& operator/=(const Type& other)
    {
        for (int i = 0; i < N; i++) _contents[i] = _contents[i] / other._contents[i];
        return *this;
    }

    // T
    Type operator/(const Value& other)
    {
        Type newVector = Type();
        for (int i = 0; i < N; i++) newVector._contents[i] = _contents[i] / other;
        return newVector;
    }

    Vector<Type, Value, N>& operator/=(const Value& other)
    {
        for (int i = 0; i < N; i++) _contents[i] = _contents[i] / other;
        return *this;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // - Const

    //const Type operator+(Type const& other) const { return operator+(const_cast<Vector<Type, Value, N>*>(this)->operator+(other)); }
    //const Type operator-(Type const& other) const { return operator-(const_cast<Vector<Type, Value, N>*>(this)->operator+(other)); }
    //const Type operator*(Type const& other) const { return operator*(const_cast<Vector<Type, Value, N>*>(this)->operator+(other)); }
    //const Type operator/(Type const& other) const { return operator/(const_cast<Vector<Type, Value, N>*>(this)->operator+(other)); }

    //Value operator+(Value const& other) const { return operator+(other); }
    //Value operator-(Value const& other) const { return operator-(other); }
    //Value operator*(Value const& other) const { return operator*(other); }
    //Value operator/(Value const& other) const { return operator/(other); }


    const Type operator+(const Type& other) const {
        Type newVector = Type();
        for (int i = 0; i < N; i++)
            newVector._contents[i] = _contents[i] + other._contents[i];
        return newVector;
    }

    const Type operator-(const Type& other) const {
        Type newVector = Type();
        for (int i = 0; i < N; i++) 
            newVector._contents[i] = _contents[i] - other._contents[i];
        return newVector;
    }

    const Type operator*(const Type& other) const {
        Type newVector = Type();
        for (int i = 0; i < N; i++) 
            newVector._contents[i] = _contents[i] * other._contents[i];
        return newVector;
    }

    const Type operator/(const Type& other) const {
        Type newVector = Type();
        for (int i = 0; i < N; i++) 
            newVector._contents[i] = _contents[i] / other._contents[i];
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

    friend std::ostream& operator<< (std::ostream& os, const Vector<Type, Value, N>& other)
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

    std::array<Value, N> _contents;
protected:
};

// All of this, just to use vector.x  :`)
class Vector3 : public Vector<Vector3, float, 3Ui64>
{
public:
    //using Vector<Vector3, float, 3Ui64>::Vector;

    Vector3() : 
        Vector<Vector3, float, 3Ui64>(), 
        x(_contents[0]),
        y(_contents[1]),
        z(_contents[2])
    {}

    // Value Constructor
    Vector3(const float& value) :
        Vector<Vector3, float, 3Ui64>(value),
        x(_contents[0]),
        y(_contents[1]),
        z(_contents[2])
    {}

    // Type Constructor
    Vector3(const Vector3& value) :
        Vector<Vector3, float, 3Ui64>(value),
        x(_contents[0]),
        y(_contents[1]),
        z(_contents[2])
    {}

    // Initializer List Constructor
    Vector3(const std::initializer_list<float>& value) :
        Vector<Vector3, float, 3Ui64>(value),
        x(_contents[0]),
        y(_contents[1]),
        z(_contents[2])
    {}

    // Specified Value Constructor 
    Vector3(float x, float y, float z) :
        Vector<Vector3, float, 3Ui64>({ x,y,z }),
        x(_contents[0]),
        y(_contents[1]),
        z(_contents[2])
    {}

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    Vector3& operator=(const Vector3& other) {
        Vector<Vector3, float, 3Ui64>::operator=(other);
        return *this;
    }

    // Cross products can only be used on Vector3s
    static Vector3 crossProduct(Vector3& v1, Vector3& v2) {
        Vector3 result = Vector3();
        result.x = v1.y * v2.z - v1.z * v2.y;
        result.y = v1.z * v2.x - v1.x * v2.z;
        result.z = v1.x * v2.y - v1.y * v2.x;
        return result;
    }

    float& x;// = _contents[0];
    float& y;// = _contents[1];
    float& z;// = _contents[2];
};

class Vector2 : public Vector<Vector2, float, 2Ui64>
{
public:
    //using Vector<Vector3, float, 3Ui64>::Vector;

    Vector2() :
        Vector<Vector2, float, 2Ui64>(),
        x(_contents[0]),
        y(_contents[1])
    {}

    // Value Constructor
    Vector2(const float& value) :
        Vector<Vector2, float, 2Ui64>(value),
        x(_contents[0]),
        y(_contents[1])
    {}

    // Type Constructor
    Vector2(const Vector2& value) :
        Vector<Vector2, float, 2Ui64>(value),
        x(_contents[0]),
        y(_contents[1])
    {}

    // Initializer List Constructor
    Vector2(const std::initializer_list<float>& value) :
        Vector<Vector2, float, 2Ui64>(value),
        x(_contents[0]),
        y(_contents[1])
    {}

    // Specified Value Constructor 
    Vector2(float x, float y) :
        Vector<Vector2, float, 2Ui64>({ x,y }),
        x(_contents[0]),
        y(_contents[1])
    {}

    // Type Constructor
    Vector2(const Vector & value) :
        Vector<Vector2, float, 2Ui64>(value),
        x(_contents[0]),
        y(_contents[1])
    {}

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    Vector2& operator=(const Vector2& other) {
        Vector<Vector2, float, 2Ui64>::operator=(other);
        return *this;
    }

    float& x;
    float& y;
};

class Vector2Int : public Vector<Vector2Int, int, 2Ui64>
{
public:

    Vector2Int() :
        Vector<Vector2Int, int, 2Ui64>(),
        x(_contents[0]),
        y(_contents[1])
    {}

    // Value Constructor
    Vector2Int(const int& value) :
        Vector<Vector2Int, int, 2Ui64>(value),
        x(_contents[0]),
        y(_contents[1])
    {}

    // Type Constructor
    Vector2Int(const Vector2Int& value) :
        Vector<Vector2Int, int, 2Ui64>(value),
        x(_contents[0]),
        y(_contents[1])
    {}

    // Initializer List Constructor
    Vector2Int(const std::initializer_list<int>& value) :
        Vector<Vector2Int, int, 2Ui64>(value),
        x(_contents[0]),
        y(_contents[1])
    {}

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    Vector2Int& operator=(Vector2Int other) {
        Vector<Vector2Int, int, 2Ui64>::operator=(other);
        return *this;
    }

    int& x;
    int& y;
};
