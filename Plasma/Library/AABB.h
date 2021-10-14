#pragma once
#include <list>

#include "Vector2.h"

// An axis aligned bounding box.
struct AABB
{
	// Functions

	Vector2 Center();
	Vector2 Extents();
	float Perimeter();
	bool Contains(const AABB& aabb);
	bool Overlaps(const AABB& aabb);

	void Combine(const AABB& aabb);
	void Combine(const AABB& aabb1, const AABB& aabb2);

	// Operators

	bool operator<<(const AABB& otherAABB);

	// Attributes

	Vector2 lowerBound;
	Vector2 upperBound;

	// Static Functions
	std::list<AABB> SortAndSweep(std::list<AABB> aabbs);



} AxisAlignedBoundingBox;

