#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <string>
#include <unordered_set>

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

template <typename TOwner, typename T>
class InputCallbackDelta : public ICallback
{
private:
    TOwner *m_instance;        
    void (TOwner::*m_function)(T&, float dt);
    T dataValue;

public:
    virtual ~InputCallbackDelta() = default;
    InputCallbackDelta(TOwner *owner, void (TOwner::*func)(T&, float dt), const T &value) : m_instance(owner), m_function(func), dataValue(value) {}

    void Call(float dt) override
    {
        (m_instance->*m_function)(dataValue, dt);
    }

    friend class InputManager;
};

class InputManager
{
private:
    std::unordered_map<SDL_Keycode, ICallback *> m_keyDownActionMap;
    std::unordered_map<SDL_Keycode, ICallback *> m_keyUpActionMap;

    std::unordered_map<std::string, SDL_Keycode> m_ActionNameKeyMap;
    std::unordered_map<SDL_Keycode, ICallback *> m_keyPressedAction;

public:
    //----for key pressed----//
    bool KEYS[355];

    template <typename T, typename TOwner>
    void BindKeyDown(InputData<T>& data, TOwner *owner, void (TOwner::*func)(T&))
    {
        // create a concrete data here
        auto callback = new InputCallback<TOwner, T>(owner, func, data.valueToBePassed);
        m_keyDownActionMap[data.key] = callback;
        m_ActionNameKeyMap[data.dataId] = data.key;
    }

    template <typename T, typename TOwner>
    void BindKeyUp(InputData<T>& data, TOwner *owner, void (TOwner::*func)(T&))
    {
        // create a concrete data here
        auto callback = new InputCallback<TOwner, T>(owner, func, data.valueToBePassed);
        m_keyUpActionMap[data.key] = callback;
    }

    template <typename T, typename TOwner>
    void BindKeyPressed(InputData<T>& data, TOwner *owner, void (TOwner::*func)(T&, float dt))
    {
        // create a concrete data here
        auto callback = new InputCallbackDelta<TOwner, T>(owner, func, data.valueToBePassed);
        m_keyPressedAction[data.key] = callback;
        m_ActionNameKeyMap[data.dataId] = data.key;
    }

    void RebindKey(const std::string& actionName, SDL_Keycode newKey);
    bool IsKeyExist(SDL_Keycode newKey);

    void OnKeyDown(SDL_Keycode key);
    void OnKeyUp(SDL_Keycode key);

    void Update(float dt);

    InputManager();
    InputManager(const InputManager &) = delete;
    ~InputManager();
    // singleton
    static InputManager &GetInstance();

    friend class InputEditorSystem;

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
