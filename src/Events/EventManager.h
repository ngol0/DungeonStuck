#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "EventType.h"
#include "EventData.h"
#include <map>
#include <vector>

template<typename TOwner, typename TData>
class EventCallback : public ICallback
{
private:
    TOwner* m_instance; //instance pointer
	void(TOwner::* m_function)(TData&); //function pointer with TData arguments (i.e: CollisionData, etc.)

public:
    EventCallback(TOwner* owner, void(TOwner::* func)(TData&)) : m_instance(owner), m_function(func) {}
    virtual ~EventCallback() = default;

    void Call(IData& data) override
    {   
        (m_instance->*m_function)(static_cast<TData&>(data));
    }
};

class EventManager
{
private:
    std::map<EventType, std::vector<std::unique_ptr<ICallback>>> listeners;

public:
    EventManager() = default;
    EventManager(const EventManager&) = delete;
    ~EventManager();

    //singleton
    static EventManager& GetInstance();
    
    //Example call in Collision System: eventManager.Notify(EventType::OnCollisionEnter, data);
    template <typename TData>
    void Notify(EventType eventType, TData data)
    {
        //find the list of callback in that event type
        auto iter = listeners.find(eventType);

        //if found
        if (iter != listeners.end())
        {
            //go through the list and call all the callbacks with args: callback.execute(args)
            for (const auto& c : iter->second)
            {
                //TData data(std::forward<TArgs>(args)...);
                c->Call(data);
            }
        }
    }

    //Example call in Damage System: eventManager->Register<CollisionData>(EventType::OnCollisionEnter, this, OnCollsionHappen);
    template <typename TData, typename TOwner>
    void Register(EventType eventType, TOwner* owner, void (TOwner::*function)(TData&))
    {
        //make a new EventCallback
        auto eventCallbackPtr = std::make_unique<EventCallback<TOwner, TData>>(owner, function);

        //add event callbacks to the map based on event type
        listeners[eventType].emplace_back(std::move(eventCallbackPtr));
    }
};

#endif