#include "EventManager.h"

EventManager& EventManager::GetInstance()
{
    static EventManager manager;
	return manager;
}

EventManager::~EventManager()
{
    // for (auto& pair : listeners)
    // {
    //     for (IEventCallback* element : pair.second)
    //     {
    //         delete element;
    //     }
    //     pair.second.clear();
    // }
    // listeners.clear();
}
