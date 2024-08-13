#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <SDL2/SDL_image.h>
#include <vector>
#include "../Global/Interface.h"

#include <spdlog/spdlog.h>

//                                  INPUT DATA & INPUT ACTION
//------------------------------------------------------------------------------------------------//
//Input Data includes:
//1. Keycode
//2. Value to be passed to callbacks (T - can be int, glm::vec2, etc.)
//==================================================================================================
//Input Action includes: a vector of input data
//==================================================================================================
//When binding an input, add an input action (i.e: move action)
//Add data into that input action: i.e: moveInput.Add(UpData(Keycode.W, glm::vec2(0,-1)));
//Then bind that input action with a callback by calling BindAction(InputAction, *owner, &callback)
//------------------------------------------------------------------------------------------------//

template<typename T>
struct InputData : public IData
{
    SDL_Keycode key;
    T valueToBePassed;

    virtual ~InputData() = default;
    InputData(SDL_Keycode key, T value) : key(key), valueToBePassed(value) {}
};

class InputAction
{
private: 
    std::string id;
    std::vector<IData*> m_inputData;

public:
    InputAction(const std::string& id="") : id(id) {}
    ~InputAction();

    //Todo: Copy constructor
    //InputAction(const InputAction& other) noexcept;
    InputAction(const InputAction& other) = delete; //for now, prevent copying

    //Todo: Copy assignment operator
    //InputAction& operator=(const InputAction& other) noexcept;

    // Move constructor
    InputAction(InputAction&& other) noexcept;

    // Move assigment operator
    InputAction& operator=(InputAction&& other) noexcept;    

    template<typename T>
    void AddKeyInputData(SDL_Keycode key, T valueToBePassed)
    {
        auto data = new InputData<T>(key, valueToBePassed);
        m_inputData.push_back(data);
    }

    const std::string& GetName() const { return id; }

    friend class InputManager;
};

#endif