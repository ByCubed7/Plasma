#pragma once

#include "Event.h"

#include <functional>
#include <map>
#include <vector>
#include <algorithm>

template<typename T>
class Dispatcher 
{
private:
    using SlotType = std::function<void(const Event<T>&)>;
    std::map<T, std::vector<SlotType>> _observers;

public:
    // Subscribe an observer
    void subscribe(T type, const SlotType& funct) 
    {
        _observers[type].push_back(funct);
    };

    // Send the event to all the observers
    void post(Event<T>& event) 
    {
        if (_observers.find(event.type()) == _observers.end())
            return;

        //Loop though all observers. If the event is not handled yet we continue to process it.
        for (auto&& observer : _observers.at(event.type())) 
        {
            if (!event.isHandled()) observer(event);
        }
    };
};

