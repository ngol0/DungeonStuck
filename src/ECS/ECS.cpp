#include "ECS.h"
#include <spdlog/spdlog.h>

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
Registry::~Registry()
{
    for (auto& s : m_systems)
    {
        delete s.second;
    }
}

void Registry::Update()
{
    //add entity
    for (const auto& e : m_entitesToBeAdded)
    {
        AddEntityToSystem(e);
    }
    m_entitesToBeAdded.clear();

    //remove entity
}

Entity Registry::CreateEntity()
{
    auto id = m_numberOfEntitnes++;
    Entity e(id);

    //todo: figure out why this is implemented this way???
    if (id >= m_entityComponentSignatures.size())
    {
        m_entityComponentSignatures.resize(id + 1);
    }

    spdlog::info("Entity Created with id: " + std::to_string(id));

    m_entitesToBeAdded.insert(e);

    return e;
}

void Registry::AddEntityToSystem(const Entity& entity)
{
    const auto entityId = entity.GetId();

    //get entity component signature
    const Signature& entityComponentSignature = m_entityComponentSignatures[entityId];
    
    //loop through all systems and get each system signature
    for (const auto& s : m_systems)
    {
        const Signature& systemSignature = s.second->GetComponentSignature();

        bool isInterested = (systemSignature & entityComponentSignature) == systemSignature;

        if (isInterested)
        {
            s.second->AddEntityToSystem(entity);
        }
    }
}