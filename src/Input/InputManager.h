#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <string>

#include "InputData.h"
#include "../Global/Interface.h"

#include <spdlog/spdlog.h>

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

template <typename TOwner, typename T>
class InputCallback : public ICallback
{
private:
    TOwner *m_instance;              // instance pointer
    void (TOwner::*m_function)(T &); // function pointer with TArgs arguments
    T dataValue;

public:
    virtual ~InputCallback() = default;
    InputCallback(TOwner *owner, void (TOwner::*func)(T &), const T &value) : m_instance(owner), m_function(func), dataValue(value) {}

    void Call() override
    {
        (m_instance->*m_function)(dataValue);
    }

    friend class InputManager;
};

class InputManager
{
private:
    std::unordered_map<SDL_Keycode, ICallback *> m_keyActionMap;
    std::unordered_map<std::string, InputAction> m_actionMap;

    template <typename T, typename TOwner>
    void BindKey(IData* data, TOwner *owner, void (TOwner::*func)(T &))
    {
        auto inputData = static_cast<InputData<T>*>(data);
        // create a concrete data here
        auto callback = new InputCallback<TOwner, T>(owner, func, inputData->valueToBePassed);

        m_keyActionMap[inputData->key] = callback;
    }

public:
    template <typename T, typename TOwner>
    void BindAction(const std::string &action, TOwner *owner, void (TOwner::*func)(T &))
    {
        auto iter = m_actionMap.find(action);
        if (iter != m_actionMap.end())
        {
            for (const auto &data : iter->second.m_inputData)
            {
                BindKey(data, owner, func);
            }
        }
    }

    InputAction& AddAction(const std::string &actionName)
    {
        InputAction input(actionName);
        m_actionMap.emplace(actionName, std::move(input));
        return m_actionMap[actionName];
    }

    void Execute(SDL_Keycode key);

    InputManager() {}
    InputManager(const InputManager &) = delete;
    ~InputManager();
    // singleton
    static InputManager &GetInstance();

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
