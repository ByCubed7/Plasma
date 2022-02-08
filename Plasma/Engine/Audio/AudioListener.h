// By @ByCubed7 on Twitter

#pragma once

#include "../Vector2.h"

#include "al.h"
#include "alc.h"

#include <iostream>
#include <vector>
#include <string>

namespace Audio
{
	/// <summary>
	/// The DEFAULT listener in the audio scene.
	/// </summary>
	class Listener {
	public:
		/// <summary> The default listener in the scene </summary>
		static Listener instance;

		Listener();
		~Listener();

		void SetPosition(Vector2 position);
		void SetVelocity(Vector2 velocity);

	private:
		Vector2 position, velocity;
		//orientation
	};
}; 

