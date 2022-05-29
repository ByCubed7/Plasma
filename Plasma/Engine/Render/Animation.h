#pragma once

#include "../FiniteStateMachine.h"
#include "../Vector.h"

#include <map>
#include <vector>

namespace Render
{
	template<typename States, typename Actions>
	class Animation : public FiniteStateMachine<States, Actions>
	{
	public:
		Vector2Int size;
		std::map<States, std::vector<Vector2Int>> data;
		double index;
		double speed;
		
		Animation(States startState) : FiniteStateMachine<States, Actions>(startState)
		{
			size = 32;
			index = 0;
			speed = 0.01;
		}

		// Add an animation to the list of the state
		void Add(States state, Vector2Int offset)
		{
			std::vector<Vector2Int>& animation = data[state];
			animation.push_back(offset);
		}

		void Transition(Actions action) {
			bool trans = this->ProcessEvent(action);
			if (trans) index = 0;
		}

		// Return the Rect the render should use
		Vector2Int Get()
		{
			// BUG: data might not have state.
			
			// Get target state
			// this->GetState()  See: https://web.archive.org/web/20130423054841/http://www.agapow.net/programming/cpp/no-arguments-that-depend-on-a-template-parameter
			std::vector<Vector2Int>& animation = data[this->GetState()];

			// BUG: vector/index may be out of bounds.
			Vector2Int target = animation[index] * size;

			return target;
		}

		void Tick()
		{
			std::vector<Vector2Int>& animation = data[this->GetState()];
			index += speed;
			if (index > animation.size()) index = index - animation.size();
		}

		void End()
		{
			index = 0;
		}

	};

}