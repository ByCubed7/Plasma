// By @ByCubed7 on Twitter

#pragma once

#include "All.h"

#include <assert.h>

namespace Tests {
	void TestVector3() {

		const Vector3 constValueA = Vector3({ 10, 3, 23 });
		const Vector3 constValueB = Vector3({ 2, 1, 6 });

		Vector3 valueA = constValueA;
		Vector3 valueB = constValueB;
		Vector3 valueC;

		// Test equality
		assert(valueA == valueA);
		assert(valueA != valueB);


		// Test operators

		// = Vector
		valueC = valueA;
		assert(valueC == valueA);

		// = T
		valueC = 1;
		assert(valueC == Vector3({ 1, 1, 1 }));


		// +
		valueC = valueA + valueB;
		assert(valueC == Vector3({ 10.0f + 2.0f, 3.0f + 1.0f, 23.0f + 6.0f }));

		// -
		valueC = valueA - valueB;
		assert(valueC == Vector3({ 10.0f - 2.0f, 3.0f - 1.0f, 23.0f - 6.0f }));

		// *
		valueC = valueA * valueB;
		assert(valueC == Vector3({ 10.0f * 2.0f, 3.0f * 1.0f, 23.0f * 6.0f }));

		// /
		valueC = valueA / valueB;
		assert(valueC == Vector3({ 10.0f / 2.0f, 3.0f / 1.0f, 23.0f / 6.0f }));


		// +=
		valueC = valueA;
		valueC = valueA + valueB;
		assert(valueC == Vector3({ 10.0f + 2.0f, 3.0f + 1.0f, 23.0f + 6.0f }));

		// -=
		valueC = valueA;
		valueC -= valueB;
		assert(valueC == Vector3({ 10.0f - 2.0f, 3.0f - 1.0f, 23.0f - 6.0f }));

		// *=
		valueC = valueA;
		valueC *= valueB;
		assert(valueC == Vector3({ 10.0f * 2.0f, 3.0f * 1.0f, 23.0f * 6.0f }));

		// /=
		valueC = valueA;
		valueC /= valueB;
		assert(valueC == Vector3({ 10.0f / 2.0f, 3.0f / 1.0f, 23.0f / 6.0f }));


		// ++
		valueC = valueA;
		assert(valueC++ == Vector3({ 10.0f, 3.0f, 23.0f }));
		assert(valueC   == Vector3({ 11.0f, 4.0f, 24.0f }));

		valueC = valueA;
		assert(++valueC == Vector3({ 11.0f, 4.0f, 24.0f }));
		assert(  valueC == Vector3({ 11.0f, 4.0f, 24.0f }));

		// --
		valueC = valueA;
		assert(valueC-- == Vector3({ 10.0f, 3.0f, 23.0f }));
		assert(valueC   == Vector3({ 9.0f, 2.0f, 22.0f }));

		valueC = valueA;
		assert(--valueC == Vector3({ 9.0f, 2.0f, 22.0f }));
		assert(  valueC == Vector3({ 9.0f, 2.0f, 22.0f }));

		// -
		valueC = -valueA;
		assert(valueC == Vector3({ -10.0f, -3.0f, -23.0f }));

		// xyz
		valueC = valueA;
		assert(valueC.x == 10.0f);
		assert(valueC.y == 3.0f);
		assert(valueC.z == 23.0f);

		// normilize
		valueC = Vector3({ 4, 0, 3 }).Normalize();
		assert(valueC == Vector3({ 0.8f, 0, 0.6f }));

		// Size
		assert(valueC.Size() == 3);
	}

}