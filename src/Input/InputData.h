#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <SDL2/SDL_image.h>
#include <vector>
#include "../Global/Interface.h"

//------------------------------------------------------------------------------------------------//
//                                  INPUT DATA & INPUT ACTION
//------------------------------------------------------------------------------------------------//
//Input Data includes:
//1. Keycode
//2. Value to be passed to callbacks (T - can be int, glm::vec2, etc.)
//==================================================================================================
//Input Action includes: a vector of input data
//==================================================================================================

template<typename T>
struct InputData : public IData
{
    std::string dataId;
    SDL_Keycode key;
    T valueToBePassed;

    virtual ~InputData() = default;
    InputData(const std::string& name, SDL_Keycode key, T value) : dataId(name), key(key), valueToBePassed(value) {}
};

template<typename T>
class InputAction
{
private: 
    std::vector<InputData<T>> m_inputData;

public:
    InputAction() = default;

    void AddKeyInputData(const std::string& actionName, SDL_Keycode key, T valueToBePassed)
    {
        m_inputData.emplace_back(InputData<T>(actionName, key, valueToBePassed)); //copy??? todo: move??
    }

    friend class InputEditorSystem;
    friend class PlayerInputSystem;
};

#endif