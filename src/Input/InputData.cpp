#include "InputData.h"

InputAction::~InputAction()
{
    for (auto &data : m_inputData)
    {
        delete data;
    }
    m_inputData.clear();
}

// Todo: Copy & Move Assignment Operation

InputAction::InputAction(InputAction &&other) noexcept : id(std::move(other.id)), m_inputData(std::move(other.m_inputData))
{
    // Reset the other vector to prevent double deletion
    other.m_inputData.clear();
    //spdlog::info("Moving resources");
}

InputAction &InputAction::operator=(InputAction &&other) noexcept
{
    // check if other is the same as this
    if (this != &other)
    {
        // clear the existing resources
        for (auto &data : m_inputData)
        {
            delete data;
        }
        m_inputData.clear();

        // move new resources to this
        id = std::move(other.id);
        m_inputData = std::move(other.m_inputData);

        // clear other's data to prevent double deletion
        other.m_inputData.clear();
    }
    return *this;
}