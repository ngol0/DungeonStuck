#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <SDL2/SDL_image.h>
#include <vector>

template<typename TValue>
struct InputData
{
    SDL_Keycode key;
    TValue valueToBePassed;

    virtual ~InputData() = default;
    InputData(SDL_Keycode key, TValue&& value) : key(key), valueToBePassed(std::forward<TValue>(value)) {}
};

template<typename TValue>
class InputAction
{
private: 
    std::vector<std::unique_ptr<InputData<TValue>>> m_inputData;

public:
    void AddKeyInputData(SDL_Keycode key, TValue&& valueToBePassed)
    {
        auto data = std::make_unique<InputData<TValue>>(key, std::forward<TValue>(valueToBePassed));
        m_inputData.emplace_back(std::move(data));
    }

    const std::vector<std::unique_ptr<InputData<TValue>>>& GetInputData() const { return m_inputData; }
};

#endif