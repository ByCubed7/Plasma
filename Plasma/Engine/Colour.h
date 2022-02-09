// By @ByCubed7 on Twitter

#pragma once

#include <glm/glm.hpp>

// An axis aligned bounding box.
struct Colour
{
	static constexpr Colour Red()	{ return Colour(255, 0, 0); }
	static constexpr Colour Green() { return Colour(0, 255, 0); }
	static constexpr Colour Blue()	{ return Colour(0, 0, 255); }
	static constexpr Colour Black() { return Colour(0, 0, 0); }
	static constexpr Colour White() { return Colour(255, 255, 255); }

	constexpr Colour(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) : red(r), green(g), blue(b), alpha(a) {}
	constexpr Colour(glm::vec3 v) : red((uint8_t) v.x * 255), green((uint8_t)v.y * 255), blue((uint8_t)v.z * 255), alpha(255) {}
	constexpr Colour() : red(0), green(0), blue(0), alpha(255) {}

	// Attributes
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
};

