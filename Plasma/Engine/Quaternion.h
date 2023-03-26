#pragma once

#include "Vector.h"

class Quaternion : public Vector<Quaternion, float, 4Ui64>
{
public:
    Quaternion() :
        Vector<Quaternion, float, 4Ui64>(),
        w(_contents[3]),
        x(_contents[0]),
        y(_contents[1]),
        z(_contents[2])
    {}

    // Value Constructor
    Quaternion(const float& value) :
        Vector<Quaternion, float, 4Ui64>(value),
        w(_contents[3]),
        x(_contents[0]),
        y(_contents[1]),
        z(_contents[2])
    {}

    // Type Constructor
    Quaternion(const Quaternion& value) :
        Vector<Quaternion, float, 4Ui64>(value),
        w(_contents[3]),
        x(_contents[0]),
        y(_contents[1]),
        z(_contents[2])
    {}

    // Initializer List Constructor
    Quaternion(const std::initializer_list<float>& value) :
        Vector<Quaternion, float, 4Ui64>(value),
        w(_contents[3]),
        x(_contents[0]),
        y(_contents[1]),
        z(_contents[2])
    {}

    // Specified Value Constructor 
    Quaternion(float w, float x, float y, float z) :
        Vector<Quaternion, float, 4Ui64>({ w,x,y,z }),
        w(_contents[3]),
        x(_contents[0]),
        y(_contents[1]),
        z(_contents[2])
    {}

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    Quaternion operator*(const Quaternion& other) const {
        return Quaternion(
            w * other.w - x * other.x - y * other.y - z * other.z,
            w * other.x + x * other.w + y * other.z - z * other.y,
            w * other.y - x * other.z + y * other.w + z * other.x,
            w * other.z + x * other.y - y * other.x + z * other.w);
    }

    Quaternion operator*(float scalar) const {
        return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
    }

    Quaternion operator/(float scalar) const {
        return Quaternion(w / scalar, x / scalar, y / scalar, z / scalar);
    }

    Quaternion& operator=(const Quaternion& other) {
        Vector<Quaternion, float, 4Ui64>::operator=(other);
        return *this;
    }

    Vector3 rotate(const Vector3& v) const {
        Quaternion v_quat(0, v.x, v.y, v.z);
        Quaternion result = (*this) * v_quat * inverse();
        return Vector3(result.x, result.y, result.z);
    }

    // Conjugate of the quaternion
    Quaternion conjugate() const { return Quaternion(w, -x, -y, -z); }

    // Inverse of the quaternion
    Quaternion inverse() const { return conjugate() / dot(); }


    float& w;
    float& x;
    float& y;
    float& z;
};
