#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <SDL2/SDL_image.h>
#include <vector>

template<typename T>
struct InputData
{
    SDL_Keycode key;
    T valueToBePassed;

    virtual ~InputData() = default;
    InputData(SDL_Keycode key, T&& value) : key(key), valueToBePassed(std::forward<T>(value)) {}
};

template<typename T>
class InputAction
{
private: 
    std::vector<std::unique_ptr<InputData<T>>> m_inputData;

public:
    void AddKeyInputData(SDL_Keycode key, T&& valueToBePassed)
    {
        auto data = std::make_unique<InputData<T>>(key, std::forward<T>(valueToBePassed));
        m_inputData.emplace_back(std::move(data));
    }

    const std::vector<std::unique_ptr<InputData<T>>>& GetInputData() const { return m_inputData; }
};

#endif