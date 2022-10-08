// By @ByCubed7 on Twitter

#pragma once

#include "Event.h"
#include "Dispatcher.h"

#include <iostream>
#include <map>


template<typename States, typename Actions>
class FiniteStateMachine {
public:

    // Event Params
    struct OnUpdateStateParams {
        OnUpdateStateParams(States currentState, Actions cause) : state(currentState), action(cause) {}
        States state;
        Actions action;
    };

    // Event Dispatchers
    Dispatcher<OnUpdateStateParams> onEnterEvent;
    Dispatcher<OnUpdateStateParams> onExitEvent;

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
    void ProcessEvent(Actions action)
    {
        std::pair<States, Actions> pair = std::make_pair(currentState, action);

        if (stateTable.find(pair) == stateTable.end()) {
            // Do NOT update the state.            
            std::cout << "Warning : Action '" << action << "' not expected while in state '" << currentState << "'" << std::endl;
            return;
        }
        
        States newState = stateTable[pair];

        // If the state has not changed then do not raise a change event.        
        if (newState == currentState) return;


        //Debug.Log("FSM - ProcessEvent =" + theAction + " : State=" + currentState + " : NewState=" + newState);        

        // Raise exit events.        
        //OnEnterEvent.Invoke(this, null);  
//        OnUpdateStateParams param = OnUpdateStateParams(currentState, action);
//        auto exitEvent = Event<OnUpdateStateParams>(param);
//        onExitEvent.Invoke(exitEvent);

        // Update state.        
        currentState = newState;

        // Raise enter events.  
//        param = OnUpdateStateParams(currentState, action);
//        auto enterEvent = Event<OnUpdateStateParams>(param);
//        onEnterEvent.Invoke(enterEvent);  
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
