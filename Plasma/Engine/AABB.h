#pragma once

#include "Vector.h"

#ifdef min
#undef min
#undef max
#endif

class AABB {
public:
    AABB() {
        min = Vector2();
        max = Vector2();
    }

    AABB(Vector2 vectorA, Vector2 vectorB) {
        min = Vector2::min(vectorA, vectorB);
        max = Vector2::max(vectorA, vectorB);
    }

    Vector2 min;
    Vector2 max;

    // Expands the box to fix the point
    void fit(Vector2 point) {
        if (min.x > point.x) min.x = point.x;
        if (min.y > point.y) min.y = point.y;
        if (max.x < point.x) max.x = point.x;
        if (max.y < point.y) max.y = point.y;
    }

    //

    static bool overlaps(const AABB& a, const AABB& b)
    {
        if (b.min.x - a.max.x > 0) return false;
        if (b.min.y - a.max.y > 0) return false;
        if (a.min.x - b.max.x > 0) return false;
        if (a.min.y - b.max.y > 0) return false;
        return true;
    }

    Vector2 center();
    Vector2 extents();
};

