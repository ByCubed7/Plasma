#pragma once

#include "Vector.h"

class Colour3 : public Vector<Colour3, __int8, 3Ui64>
{
public:
    Colour3() :
        Vector<Colour3, __int8, 3Ui64>(),
        r(_contents[0]),
        g(_contents[1]),
        b(_contents[2])
    {}

    // Value Constructor
    Colour3(const __int8& value) :
        Vector<Colour3, __int8, 3Ui64>(value),
        r(_contents[0]),
        g(_contents[1]),
        b(_contents[2])
    {}

    // Type Constructor
    Colour3(const Colour3& value) :
        Vector<Colour3, __int8, 3Ui64>(value),
        r(_contents[0]),
        g(_contents[1]),
        b(_contents[2])
    {}

    // Initializer List Constructor
    Colour3(const std::initializer_list<__int8>& value) :
        Vector<Colour3, __int8, 3Ui64>(value),
        r(_contents[0]),
        g(_contents[1]),
        b(_contents[2])
    {}

    // Specified Value Constructor 
    Colour3(__int8 r, __int8 g, __int8 b) :
        Vector<Colour3, __int8, 3Ui64>({ r,g,b }),
        r(_contents[0]),
        g(_contents[1]),
        b(_contents[2])
    {}

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    Colour3& operator=(const Colour3& other) {
        Vector<Colour3, __int8, 3Ui64>::operator=(other);
        return *this;
    }

    __int8& r;
    __int8& g;
    __int8& b;
};


class Colour4 : public Vector<Colour4, __int8, 4Ui64>
{
public:
    Colour4() :
        Vector<Colour4, __int8, 4Ui64>(),
        r(_contents[0]),
        g(_contents[1]),
        b(_contents[2]),
        a(_contents[3])
    {}

    // Value Constructor
    Colour4(const __int8& value) :
        Vector<Colour4, __int8, 4Ui64>(value),
        r(_contents[0]),
        g(_contents[1]),
        b(_contents[2]),
        a(_contents[3])
    {}

    // Type Constructor
    Colour4(const Colour4& value) :
        Vector<Colour4, __int8, 4Ui64>(value),
        r(_contents[0]),
        g(_contents[1]),
        b(_contents[2]),
        a(_contents[3])
    {}

    // Initializer List Constructor
    Colour4(const std::initializer_list<__int8>& value) :
        Vector<Colour4, __int8, 4Ui64>(value),
        r(_contents[0]),
        g(_contents[1]),
        b(_contents[2]),
        a(_contents[3])
    {}

    // Specified Value Constructor 
    Colour4(__int8 r, __int8 g, __int8 b, __int8 a) :
        Vector<Colour4, __int8, 4Ui64>({ r,g,b,a }),
        r(_contents[0]),
        g(_contents[1]),
        b(_contents[2]),
        a(_contents[3])
    {}

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    Colour4& operator=(const Colour4& other) {
        Vector<Colour4, __int8, 4Ui64>::operator=(other);
        return *this;
    }

    __int8& r;
    __int8& g;
    __int8& b;
    __int8& a;
};
