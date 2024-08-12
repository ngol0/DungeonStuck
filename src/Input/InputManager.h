#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <spdlog/spdlog.h>
#include "InputData.h"

class IAction
{
public:
    virtual ~IAction() = default;
    virtual void Execute() = 0;
};

// Action class with TArgs as argument
// template<typename TOwner, typename... TArgs>
// class Action : public IAction
// {
// private:
// 	TOwner* m_instance; //instance pointer
// 	void(TOwner::* m_function)(TArgs...); //function pointer with TArgs arguments
// public:
//     virtual ~Action() = default;
//     Action(TOwner* owner, void(TOwner::* func)(TArgs...)) : m_instance(owner), m_function(func) {}
//     void Execute(TArgs&&...args)
//     {
//         (m_instance->*m_function)(std::forward<TArgs>(args)...);
//     }
// };

template<typename TOwner, typename TValue>
class Action : public IAction
{
private:
	TOwner* m_instance; //instance pointer
	void(TOwner::* m_function)(TValue&); //function pointer with TArgs arguments
    TValue dataValue;

public:
    virtual ~Action() = default;
    Action(TOwner* owner, void(TOwner::* func)(TValue&), const TValue& value) : m_instance(owner), m_function(func), dataValue(value) {}

    void Execute()
    {
        (m_instance->*m_function)(dataValue);
    }

    friend class InputManager;
};

class InputManager
{
private:
    std::unordered_map<SDL_Keycode, IAction*> m_keyActionMap;

public:
    template<typename TValue, typename TOwner>
    void BindKey(const InputData<TValue>& data, TOwner* owner, void(TOwner::* func)(TValue&))
    {
        //create a concrete data here
        auto action = new Action<TOwner, TValue>(owner, func, data.valueToBePassed);

        m_keyActionMap[data.key] = action;
    }

    void Execute(SDL_Keycode key)
    {
        auto iter = m_keyActionMap.find(key);
	    if (iter != m_keyActionMap.end())
	    {
		    iter->second->Execute();
	    }
    }

    InputManager() {}
    InputManager(const InputManager&) = delete;
    ~InputManager();
    //singleton
    static InputManager& GetInstance();

    //---Not in use anymore--//
    // Bind Key with TArgs...
    // template<typename TOwner, typename... TArgs>
    // void BindKey(SDL_Keycode key, TOwner* owner, void(TOwner::* func)(TArgs...))
    // {
    //     //auto action = std::make_unique<Action<TOwner, TArgs...>>(owner, func);
    //     //m_keyActionMap[key] = std::move(action);
    //     auto action = new Action<TOwner, TArgs...>(owner, func);
    //     m_keyActionMap[key] = action;
    // }

    // Execute with TArgs...
    // template<typename TOwner, typename...TArgs>
    // void Execute(SDL_Keycode key, TArgs&&...args)
    // {
    //     auto iter = m_keyActionMap.find(key);
	//     if (iter != m_keyActionMap.end())
	//     {
	// 	    auto action = static_cast<Action<TOwner, TArgs...>*>(iter->second);
    //         action->Execute(std::forward<TArgs>(args)...);
	//     }
    // }
};

#endif
