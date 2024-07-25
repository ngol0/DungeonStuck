#include "ECS.h"

//-------Entity-----------------//
Entity::Entity(int id, Registry& registry) : m_id(id), m_registry(&registry)
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
    for (auto& pair : m_systems)
    {
        delete pair.second;
    }

    for (auto& pool : m_componentPools)
    {
        delete pool;
    }
}

void Registry::Update(float dt)
{
    //update all systems
    for (const auto& pair : m_systems)
    {
        pair.second->Update(dt);
    }

    //add entity
    for (const auto& e : m_entitesToBeAdded)
    {
        AddEntityToSystem(e);
    }
    m_entitesToBeAdded.clear();

    //remove entity
}

void Registry::Render(SDL_Renderer* renderer)
{
    for (const auto& pair : m_systems)
    {
        pair.second->Render(renderer);
    }
}

Entity Registry::CreateEntity()
{
    auto id = m_numberOfEntitnes++;
    Entity e(id, *this);

    //todo: figure out why this is implemented this way???
    if (id >= m_entityComponentSignatures.size())
    {
        m_entityComponentSignatures.resize(id + 1);
    }

    //spdlog::info("Entity Created with id: " + std::to_string(id));

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