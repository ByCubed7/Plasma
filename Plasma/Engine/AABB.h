// By @ByCubed7 on Twitter

#pragma once

#include <list>
#include "Vector.h"

// An axis aligned bounding box.
struct AABB
{
	// Constructor
	AABB();
	AABB(Vector2 lower, Vector2 upper);
	AABB(Vector2 bounds);
	AABB(float length);

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
	//std::list<AABB> SortAndSweep(std::list<AABB> aabbs);



};// AxisAlignedBoundingBox;

