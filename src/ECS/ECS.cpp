#include "ECS.h"

//-------Entity-----------------//
Entity::Entity(int id) : m_id(id)
{   

}


//-------------System-------------//
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

//--------------Registry------------//
void Registry::Update()
{

}

Entity Registry::CreateEntity()
{
    int id = m_numberOfEntitnes++;
    Entity e(id);
    m_entitesToBeAdded.insert(e);

    return e;
}

void Registry::AddEntityToSystem(const Entity& entity)
{
    
}