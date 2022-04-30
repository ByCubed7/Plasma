// By @ByCubed7 on Twitter

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
    std::map < T, std::vector<SlotType> > observers;

public:
    // Subscribe an observer
    void Subscribe(T type, const SlotType& funct) 
    {
        observers[type].push_back(funct);
    };

    // Send the event to all the observers
    void Invoke(Event<T>& event)
    {
        if (observers.find(event.type()) == observers.end())
            return;

        for (auto&& observer : observers.at(event.type())) 
        {
            if (!event.isHandled()) observer(event);
        }
    };
};

