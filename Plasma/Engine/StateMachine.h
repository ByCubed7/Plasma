// By @ByCubed7 on Twitter

#pragma once
#include <iostream>
#include <map>

template<enum States, enum Actions>
class FiniteStateMachine {
public:

    //public event EventHandler StateExitEv;    
    //public event EventHandler StateEnterEv;

    FSM(States startState, std::map<std::pair<States, Actions>, States> _stateMatrix)
    {
        stateMatrix = _stateMatrix;
        currentState = startState;
    }

protected:
    void ProcessEvent(Actions theAction)
    {
        States newState = stateMatrix[std::make_pair(currentState, theAction)];

        // If the state has not changed then do not raise a change event.        
        if (newState == currentState) return;

        if (newState == 0) {
            // Do NOT update the state.            
            std::cout << "Warning : Action '" << theAction << "' not expected while in this state '" << currentState << "'" << std::endl;
            return;
        }
        //Debug.Log("FSM - ProcessEvent =" + theAction + " : State=" + currentState + " : NewState=" + newState);        

        // Raise exit events.        
        //StateExitEv?.Invoke(this, null);        

        // Update state.        
        currentState = newState;

        // Raise enter events.          
        //StateEnterEv?.Invoke(this, null);    
    }

    States GetState() {
        return state;
    }

    void SetState(States newState) {
        currentState = newState;
    }

private:
    States currentState;
    std::map<std::pair<States, Actions>, Actions> stateMatrix;
};

