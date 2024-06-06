#include "ECS.h"

/// @brief Entity
/// @param Implementatin of Entity 
Entity::Entity(int id) : m_id(id)
{   

}


/// @brief System
void System::AddEntityToSystem(const Entity& entity)
{
    m_entities.push_back(entity);
}

void System::RemoveEntityFromSystem(const Entity& entity)
{
    auto iter = std::remove_if(m_entities.begin(), m_entities.end(), 
        [&](const Entity& other) { return other == entity; });
    m_entities.erase(iter, m_entities.end());
}
