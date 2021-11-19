#pragma once

#include "Event.h"

#include <functional>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
class Dispatcher 
{
private:
    using SlotType = function<void(const Event<T>&)>;
    map < T, vector<SlotType> > observers;

public:
    // Subscribe an observer
    void subscribe(T type, const SlotType& funct) 
    {
        observers[type].push_back(funct);
    };

    // Send the event to all the observers
    void post(Event<T>& event) 
    {
        if (observers.find(event.type()) == observers.end())
            return;

        for (auto&& observer : observers.at(event.type())) 
        {
            if (!event.isHandled()) observer(event);
        }
    };
};

