#include "AABB.h"

// Returns the center of the box
Vector2 AABB::center()
{
    return (min + max) * 0.5f;
}

// Returns the extents of the box
Vector2 AABB::extents()
{
    return (max - min) * 0.5f;
}

// Returns the perimeter of the box
//float AABB::perimeter()
//{
//    float wx = upperBound.x - lowerBound.x;
//    float wy = upperBound.y - lowerBound.y;
//    return (wx + wy) * 2.0f;
//}
