#include "AABB.h"

// Returns the center of the box
Vector2 AABB::Center()
{
    return (lowerBound + upperBound) * 0.5f;
}

// Returns the extents of the box
Vector2 AABB::Extents()
{
    return (upperBound - lowerBound) * 0.5f;
}

// Returns the perimeter of the box
float AABB::Perimeter()
{
    float wx = upperBound.x - lowerBound.x;
    float wy = upperBound.y - lowerBound.y;
    return (wx + wy) * 2.0f;
}

// Whether the box contains the given box
bool AABB::Contains(const AABB& aabb)
{
    bool contains = true;
    // Would &= work in this scenario?
    contains = contains && lowerBound.x <= aabb.lowerBound.x;
    contains = contains && lowerBound.y <= aabb.lowerBound.y;
    contains = contains && aabb.upperBound.x <= upperBound.x;
    contains = contains && aabb.upperBound.y <= upperBound.y;
    return contains;
}

// Whether the box overlaps the given box
bool AABB::Overlaps(const AABB& aabb)
{
    if (aabb.lowerBound.x > upperBound.x || aabb.lowerBound.y > upperBound.y) return false;
    if (lowerBound.x > aabb.upperBound.x || lowerBound.y > aabb.upperBound.y) return false;
    return true;
}

//

// Merge this box with another
void AABB::Combine(const AABB& aabb)
{
    lowerBound = Vector2::Min(lowerBound, aabb.lowerBound);
    upperBound = Vector2::Max(upperBound, aabb.upperBound);
}

// Combine 2 boxes and assign the bounds to this box
// Should we change this to a constructor?
void AABB::Combine(const AABB& aabb1, const AABB& aabb2)
{
    lowerBound = Vector2::Min(aabb1.lowerBound, aabb2.lowerBound);
    upperBound = Vector2::Max(aabb1.upperBound, aabb2.upperBound);
}

//

bool AABB::operator<<(const AABB& otherAABB)
{
    return Overlaps(otherAABB);
}