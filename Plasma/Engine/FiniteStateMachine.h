#pragma once

#include <iostream>
#include <map>

namespace Engine
{
    template<typename States, typename Actions>
    class FiniteStateMachine {
    public:

        //event EventHandler StateExitEv;    
        //event EventHandler StateEnterEv;

        FiniteStateMachine(States startState)
        {
            currentState = startState;
            stateTable = std::map<std::pair<States, Actions>, States>();
        }

        void AddTransition(States fromState, Actions action, States newState) {
            std::pair<States, Actions> pair = std::make_pair(fromState, action);
            stateTable[pair] = newState;
        }

    protected:
        // Returns whether the event changed the state
        bool ProcessEvent(Actions action)
        {
            std::pair<States, Actions> pair = std::make_pair(currentState, action);

            if (stateTable.count(pair) == 0) {
                // Do NOT update the state.            
                //std::cout << "Warning : Action '" << action << "' not expected while in state '" << currentState << "'" << std::endl;
                //std::cout << "Action '" << action << "' in state '" << currentState << "'" << std::endl;
                return false;
            }

            States newState = stateTable[pair];

            // If the state has not changed then do not raise a change event.        
            if (newState == currentState) return false;

            //Debug.Log("FSM - ProcessEvent =" + theAction + " : State=" + currentState + " : NewState=" + newState);        

            // Raise exit events.        
            //StateExitEv.Invoke(this, null);        

            // Update state.        
            currentState = newState;

            // Raise enter events.          
            //StateEnterEv.Invoke(this, null);   
            return true;
        }



        States GetState() {
            return currentState;
        }

        void SetState(States newState) {
            currentState = newState;
        }

    private:
        States currentState;
        std::map<std::pair<States, Actions>, States> stateTable;
    };

}
